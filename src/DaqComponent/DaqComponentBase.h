// -*- C++ -*-
/*!
 * @file DaqComponentBase.h
 * @brief DAQ Component Base class
 * @date
 * @author Yoshiji Yasu, Kazuo Nakayoshi
 *
 * Copyright (C) 2008
 *     Yoshiji Yasu, Kazuo Nakayoshi
 *     Electronics System Group,
 *     KEK, Japan.
 *     All rights reserved.
 *
 */

#ifndef DAQCOMPONENTBASE_H
#define DAQCOMPONENTBASE_H

#include <iostream>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/DataPortStatus.h>

#include "DAQServiceSVC_impl.h"
#include "DAQService.hh"
#include "DaqComponentException.h"
#include "Timer.h"

namespace DAQMW
{
    class DaqComponentBase:
	public RTC::DataFlowComponentBase
    {

    public:
	DaqComponentBase(RTC::Manager* manager)
	    : RTC::DataFlowComponentBase(manager),
	      m_trans_lock(false), m_DAQServicePort("DAQService"),
	      m_comp_name("NONAME"), m_command(CMD_NOP),
	      m_state(LOADED), m_state_prev(LOADED),
	      m_runNumber(0),
	      m_eventByteSize(0), m_loop(0), m_total_event(0), m_total_size(0),
	      m_isOnError(false), 
	      m_isTimerAlarm(false),
	      m_debug(false)
	{
	    mytimer = new Timer(STATUS_CYCLE_SEC);
	}
	
	virtual ~DaqComponentBase()
	{
	    delete mytimer;
	}

	enum BufferStatus {BUF_FATAL = -1, BUF_SUCCESS, BUF_TIMEOUT, BUF_NODATA, BUF_NOBUF};

    protected:
	static const int DAQ_CMD_SIZE      = 10;
	static const int DAQ_STATE_SIZE    =  6;
	static const int DAQ_IDLE_TIME_SEC =  1;
	static const int STATUS_CYCLE_SEC  =  2;

	typedef int (DAQMW::DaqComponentBase::*DAQFunc)();

	DAQFunc m_daq_trans_func[DAQ_CMD_SIZE];
	DAQFunc m_daq_do_func[DAQ_STATE_SIZE];

	bool m_trans_lock;
	DAQServiceSVC_impl m_daq_service0;
	RTC::CorbaPort m_DAQServicePort;

	Timer* mytimer;
	std::string m_comp_name;
	DAQCommand m_command;
	DAQCommand m_old_command;
	DAQLifeCycleState m_state;
	DAQLifeCycleState m_state_prev;
	Status m_status;
	unsigned int m_runNumber;
	unsigned m_eventByteSize;        
	unsigned long long m_loop;
	unsigned long long m_total_event;
	unsigned long long m_total_size;

	std::string m_err_message;

	bool      m_isOnError;
	bool      m_isTimerAlarm;
	bool      m_debug;


        static const unsigned int  HEADER_BYTE_SIZE = 8;
        static const unsigned int  FOOTER_BYTE_SIZE = 8;
        static const unsigned char HEADER_MAGIC     = 0xe7;
        static const unsigned char FOOTER_MAGIC     = 0xcc;
        static const unsigned int  EVENT_BUF_OFFSET = HEADER_BYTE_SIZE;


        /**
         *  The data structure transferring between DAQ-Components is
         *  Header data(8bytes) + Event data(8bytes x num_of_events) + Footer data(8bytes).
         *
         *  Header data includes magic number(2bytes), and data byte size(4bytes) 
         *  except header and footer.
         *  Footer data includes magic number(2bytes), sequence number(4bytes).
         *
         *                dat[0]   dat[1]   dat[2]    dat[3]   dat[4]     dat[5]     dat[6]    dat[7]
         *  Header        0xe7     0xe7     reserved  reserved siz(24:31) siz(16:23) siz(8:15) siz(0:7)
         *  Event data1
         *  ...
         *  Event dataN
         *  Footer        0xcc     0xcc     reserved  reserved seq(24:31) seq(16:23) seq(8:15) seq(0:7)
         */

        int set_header(unsigned char* header, unsigned data_byte_size) {
            header[0] = HEADER_MAGIC;
            header[1] = HEADER_MAGIC;
            header[2] = 0;
            header[3] = 0;
            header[4] = (data_byte_size & 0xff000000) >> 24;
            header[5] = (data_byte_size & 0x00ff0000) >> 16;
            header[6] = (data_byte_size & 0x0000ff00) >>  8;
            header[7] = (data_byte_size & 0x000000ff);
            return 0;
        }

        int set_footer(unsigned char* footer, unsigned sequence_num) 
        {
            footer[0] = FOOTER_MAGIC;
            footer[1] = FOOTER_MAGIC;
            footer[2] = 0;
            footer[3] = 0;
            footer[4] = (sequence_num & 0xff000000) >> 24;
            footer[5] = (sequence_num & 0x00ff0000) >> 16;
            footer[6] = (sequence_num & 0x0000ff00) >>  8;
            footer[7] = (sequence_num & 0x000000ff);
            return 0;
        }

        bool check_header(unsigned char* header, unsigned received_byte) 
        {
            bool ret = false;

            if (header[0] == HEADER_MAGIC && header[1] == HEADER_MAGIC) {
                unsigned int event_size = (  header[4] << 24 ) 
                                         + ( header[5] << 16 )
                                         + ( header[6] <<  8 )
                                         +   header[7];
                if (received_byte == event_size) {
                    ret = true;
                }
                else {
                    std::cerr << "### ERROR: Event byte size missmatch" << std::endl;
                }
            }
            else {
                std::cerr << "### ERROR: Bad Magic Num:" 
                          << std::hex << (unsigned)header[0] << " " << (unsigned)header[1] << std::endl;
            }
            std::cerr << std::dec;
            return ret;
        }

        bool check_footer(unsigned char* footer, unsigned loop_cnt) 
        {
            bool ret = false;
            if (footer[0] == FOOTER_MAGIC && footer[1] == FOOTER_MAGIC) {
                unsigned int seq_num = (  footer[4] << 24 )
                                      + ( footer[5] << 16 )
                                      + ( footer[6] <<  8 )
                                      +   footer[7];
                if (seq_num == loop_cnt) {
                    ret = true;
                }
                else {
                    std::cerr << "### ERROR: Sequence No. missmatch" << std::endl;
                    std::cerr << "sequece no. in footer :" << seq_num << std::endl;
                    std::cerr << "loop cnts at component:" << loop_cnt << std::endl;
                }
            }
            return ret;
        }


	int init_command_port()
	{
	    // Set service provider to Ports
	    m_DAQServicePort.registerProvider("daq_svc", "DAQService", m_daq_service0);
  
	    // Set CORBA Service Ports
	    registerPort(m_DAQServicePort);

	    return 0;
	}

	int set_comp_name(char* name)
	{
	    m_comp_name = name;
	    return 0;
	}

	bool check_trans_lock(){
	    return m_trans_lock;
	}

	void set_trans_lock(){
	    m_trans_lock = true;
	}

	void set_trans_unlock(){
	    m_trans_lock = false;
	}

	int transAction(int command) {
	    return (this->*m_daq_trans_func[command])();
	}

	void doAction(int state){
	    (this->*m_daq_do_func[state])();
	}

	virtual int daq_dummy()       = 0;
	virtual int daq_configure()   = 0;
	virtual int daq_unconfigure() = 0;
	virtual int daq_start()       = 0;
	virtual int daq_run()         = 0;
	virtual int daq_stop()        = 0;
	virtual int daq_pause()       = 0;
	virtual int daq_resume()      = 0;

	int daq_base_dummy()
	{
	    daq_dummy();
	    set_status(COMP_WORKING);
	    sleep(DAQ_IDLE_TIME_SEC);
	    return 0;
	}

	int daq_base_configure()
	{
	    set_status(COMP_WORKING);
	    daq_configure();

	    return 0;
	}

	int daq_base_unconfigure()
	{
	    m_total_size = 0;
	    set_status(COMP_WORKING);
	    daq_unconfigure();

	    return 0;
	}

	int daq_base_start()
	{
	    m_total_size = 0;
	    m_loop = 0;
	    set_status(COMP_WORKING);
	    daq_start();

	    return 0;
	}

	int daq_base_stop()
	{

	    if (m_isOnError) {
		m_isOnError = false; /// reset error flag
		std::cerr << "*** Error flag was reset\n";
	    }

	    m_err_message = "";
	    set_status(COMP_WORKING);
	    daq_stop();

	    std::cerr << "event byte size = " << m_total_size << std::endl;
	    return 0;
	}

	int daq_base_pause()
	{
	    set_status(COMP_WORKING);
	    daq_pause();

	    return 0;
	}

	int get_command()
	{
	    m_command = m_daq_service0.getCommand();
	    if (m_debug) {
		std::cerr << "Dispatcher: m_command=" << m_command << std::endl;
	    }

	    return 0;
	}

	int set_done()
	{
	    m_daq_service0.setDone();
	    if (m_debug) {
		std::cerr << "Dispatcher::set_done()\n";
	    }

	    return 0;
	}

	virtual int parse_params( ::NVList* list ) = 0;

	int daq_onError(){
	    m_isOnError = true;
	    if (check_trans_lock()) {
		set_trans_unlock();
	    }
	    std::cerr << "### daq_onError(): ERROR Occured\n";
	    std::cerr << m_err_message << std::endl;
	    set_status(COMP_FATAL);
	    sleep(1);

	    return 0;
	}

	int set_status(CompStatus comp_status)
	{
	    Status* mystatus = new Status;
	    mystatus->comp_name = CORBA::string_dup(m_comp_name.c_str());
	    mystatus->state = m_state;
	    ///mystatus->event_num = m_total_event;
	    mystatus->event_size = m_total_size;
	    mystatus->comp_status = comp_status;

	    m_daq_service0.setStatus(*mystatus);
	    
	    return 0;
	}

        void fatal_error_report(FatalType::Enum type, int code = -1)
        {
            m_isOnError = true;
            set_status(COMP_FATAL);
            throw DaqCompDefinedException(type, code);
        }
 
        void fatal_error_report(FatalType::Enum type, const char* desc, int code = -1)
        {
            m_isOnError = true;
            set_status(COMP_FATAL);
            throw DaqCompUserException(type, desc, code);
        }

        void fatal_report_to_operator(FatalType::Enum type, const char* desc, int code = -1)
        {
            FatalErrorStatus errStatus;
            errStatus.fatalTypes = type;
            errStatus.errorCode  = code;
            errStatus.description = CORBA::string_dup(desc);
            m_daq_service0.setFatalStatus(errStatus);
        }

	void init_state_table() 
	{
	    m_daq_trans_func[CMD_CONFIGURE]   = &DAQMW::DaqComponentBase::daq_base_configure;
	    m_daq_trans_func[CMD_START]       = &DAQMW::DaqComponentBase::daq_base_start;
	    m_daq_trans_func[CMD_PAUSE]       = &DAQMW::DaqComponentBase::daq_pause;
	    m_daq_trans_func[CMD_RESUME]      = &DAQMW::DaqComponentBase::daq_resume;
	    m_daq_trans_func[CMD_STOP]        = &DAQMW::DaqComponentBase::daq_base_stop;
	    m_daq_trans_func[CMD_UNCONFIGURE] = &DAQMW::DaqComponentBase::daq_base_unconfigure;

	    m_daq_do_func[LOADED]     = &DAQMW::DaqComponentBase::daq_base_dummy;
	    m_daq_do_func[CONFIGURED] = &DAQMW::DaqComponentBase::daq_base_dummy;
	    m_daq_do_func[RUNNING]    = &DAQMW::DaqComponentBase::daq_run;
	    m_daq_do_func[PAUSED]     = &DAQMW::DaqComponentBase::daq_base_dummy;
	}

	int reset_timer() 
	{
	    mytimer->resetTimer();

	    return 0;
	}

	int clockwork_status_report() 
	{
	    if (mytimer->checkTimer()) {
		m_isTimerAlarm = true;
		set_status(COMP_WORKING);
		mytimer->resetTimer();
	    }
	    return 0;
	}


	BufferStatus check_outPort_status(RTC::OutPort<RTC::TimedOctetSeq> & myOutPort)
	{
	    BufferStatus ret = BUF_SUCCESS;
	    int index = 0;
	    RTC::DataPortStatus::Enum out_status = myOutPort.getStatus(index);
	    
	    switch(out_status) {
	    case RTC::DataPortStatus::PORT_OK:
		ret = BUF_SUCCESS;
		//std::cerr << "BUF_SUCCESS\n";
		break;
	    case RTC::DataPortStatus::SEND_TIMEOUT:
	    case RTC::DataPortStatus::BUFFER_TIMEOUT:
	    case RTC::DataPortStatus::SEND_FULL:
	    case RTC::DataPortStatus::RECV_EMPTY:
	    case RTC::DataPortStatus::RECV_TIMEOUT:
		ret = BUF_TIMEOUT;
		std::cerr << "BUF_TIMEOUT\n";
		break;
	    case RTC::DataPortStatus::BUFFER_FULL:
		ret = BUF_NOBUF;
		break;
	    case RTC::DataPortStatus::BUFFER_EMPTY:
		ret = BUF_NODATA;
		break;
	    case RTC::DataPortStatus::BUFFER_ERROR:
	    case RTC::DataPortStatus::PORT_ERROR:
	    case RTC::DataPortStatus::INVALID_ARGS:
	    case RTC::DataPortStatus::PRECONDITION_NOT_MET:
	    case RTC::DataPortStatus::CONNECTION_LOST:
	    case RTC::DataPortStatus::UNKNOWN_ERROR:
		ret = BUF_FATAL;
		break;
	    }
	    return ret;
	}

	bool check_dataPort_connections(RTC::OutPort<RTC::TimedOctetSeq> & myOutPort)
	{
	    //const std::vector<RTC::OutPortConnector*>& conn_list = myOutPort.connectors();
	    coil::vstring conn_list = myOutPort.getConnectorIds();
	    bool ret = false;
	    if( conn_list.size() == 1) {
		ret = true;
	    }
	    return ret;
	}

	bool check_dataPort_connections(RTC::InPort<RTC::TimedOctetSeq> & myInPort)
	{
/*
	    const std::vector<RTC::InPortConnector*>& conn_list = myInPort.connectors();
*/
	    coil::vstring conn_list = myInPort.getConnectorIds();
	    bool ret = false;
	    if( conn_list.size() == 1) {
		ret = true;
	    }
	    return ret;
	}

        bool set_state(DAQCommand command)
        {
            bool ret = true;
            /// new command has come, chage new state
            switch (command) {
            case CMD_CONFIGURE:
                m_state_prev = LOADED;
                m_state = CONFIGURED;
                break;
            case CMD_START:
                m_state_prev = CONFIGURED;
                m_state = RUNNING;
                break;
            case CMD_PAUSE:
                m_state_prev = RUNNING;
                m_state = PAUSED;
                set_trans_lock();
                break;
            case CMD_RESUME:
                m_state_prev = PAUSED;
                m_state = RUNNING;
                break;
            case CMD_STOP:
                m_state_prev = RUNNING;
                m_state = CONFIGURED;
                set_trans_lock();
                break;
            case CMD_UNCONFIGURE:
                m_state_prev = RUNNING;
                m_state = LOADED;
                break;
            default:
                //status = false;
                ret = false;
                break;
            }       
            return ret;
        }


	int daq_do() 
	{
	    int ret = 0;
	    get_command();
	    
	    bool status = true;

	    if (m_command != CMD_NOP) {
		status = set_state(m_command);	

		if (status) {
		    while (check_trans_lock()) {
			if (m_debug) {
			    std::cerr << "### trans locked" << std::endl;
			}
			usleep(0);
			if ( !m_isOnError ) {
			    try {
				doAction(m_state_prev);
			    }
			    catch(DaqCompDefinedException& e ) {
				std::cerr << mytimer->getDate() << " ";
				FatalType::Enum mytype = e.type();
				int mycode             = e.reason();
				const char* mydesc     = e.what();
				fatal_report_to_operator(mytype, mydesc, mycode);
			    }
			    catch(DaqCompUserException& e) {
				std::cerr << mytimer->getDate() << " ";
				FatalType::Enum mytype = e.type();
				int mycode             = e.reason();
				const char* mydesc     = e.what();
				fatal_report_to_operator(mytype, mydesc, mycode);				
			    }
			    catch(...) {
				std::cerr << "### got unknown exception at transition\n";
			    }
			}
			else {
			    daq_onError();
			}
		    }
		    ///valid command, do action as transition
		    try {
			ret = transAction(m_command);
		    }
                    catch(DaqCompDefinedException& e ) {
                        std::cerr << mytimer->getDate() << " ";
                        FatalType::Enum mytype = e.type();
                        int mycode             = e.reason();
                        const char* mydesc     = e.what();
                        fatal_report_to_operator(mytype, mydesc, mycode);
                    }
                    catch(DaqCompUserException& e) {
			std::cerr << mytimer->getDate() << " ";
			FatalType::Enum mytype = e.type();
			int mycode             = e.reason();
			const char* mydesc     = e.what();
			fatal_report_to_operator(mytype, mydesc, mycode);
                    }
                    catch(...) {
                        std::cerr << "### got unknown exception at transition\n";
                    }
		    set_status(COMP_WORKING);
		}
		else {
		    std::cerr << "daq_do: transAction call: illegal command" 
			      << std::endl;
		}
		set_done();
	    } else {
		///same command as previous, stay same state, do same action
		if ( !m_isOnError ) {
		    try {
			doAction(m_state);
		    }
                    catch(DaqComponentException& e) {
                        std::cerr << mytimer->getDate() << " ";
                        std::cerr << "### caught daq exp:" << e.what() << std::endl;
                    }
                    catch(...) {
                        std::cerr << "---- caught exception on DaqComponentBase\n";
                        return ret;
                    }
		    clockwork_status_report();
		}
		else {
		    daq_onError();
		}
	    }
	    return ret;
	} /// daq_do()
    }; /// class
} /// namespace

#endif