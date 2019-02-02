include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../lib/SiTCP/CPP/Sock
  ${CMAKE_CURRENT_SOURCE_DIR}/../DaqComponent/idl
  ${CMAKE_CURRENT_BINARY_DIR}
  ${OPENRTM_INCLUDE_DIRS}
  )

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/../lib/SiTCP/CPP/Sock 
  ${OPENRTM_LIBRARY_DIRS}
  )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(daq_idl "${CMAKE_CURRENT_SOURCE_DIR}/../DaqComponent/idl/DAQService.idl")
#message("daq_idl: ${daq_idl}")

add_custom_command(
 OUTPUT DAQService.hh DAQServiceSK.cc DAQServiceDynSK.cc DAQServiceSkel.h DAQServiceStub.h DAQServiceSkel.cpp DAQServiceStub.cpp 
 DEPENDS ${daq_idl}
 COMMAND ${OPENRTM_IDLC} ${OPENRTM_IDLFLAGS} -I${OPENRTM_INCLUDE_DIR}/rtm/idl ${daq_idl}
 COMMAND ${OPENRTM_IDL_WRAPPER} ${OPENRTM_IDL_WRAPPER_FLAGS} --idl-file=${daq_idl}
 )

add_executable(DaqOperatorComp 
  DaqOperator.cpp
  DaqOperatorComp.cpp
  ConfFileParser.cpp
  CreateDom.cpp
  DAQService.hh
  DAQServiceSkel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../DaqComponent/idl/DAQServiceSVC_impl.cpp
  )

target_link_libraries(DaqOperatorComp
  ${OPENRTM_LIBRARIES}
  Sock xerces-c
)

install(FILES
  ComponentInfoContainer.h
  ConfFileParser.cpp
  ConfFileParser.h
  CreateDom.cpp
  CreateDom.h
  DaqOperator.cpp
  DaqOperator.h
  DaqOperatorComp.cpp
  Parameter.h
  ParameterServer.h
  callback.h
  DESTINATION ${PROJECT_INSTALL_DATADIR}/DaqOperator
  )

install(FILES
  Makefile.in
  DESTINATION ${PROJECT_INSTALL_DIR}/libexec 
  RENAME Makefile
  )

install(TARGETS
  DaqOperatorComp
  RUNTIME DESTINATION ${PROJECT_INSTALL_DIR}/libexec
  )
