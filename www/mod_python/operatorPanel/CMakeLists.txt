include(${CMAKE_SOURCE_DIR}/www/Distributions.cmake)

configure_file(writedata.py.in writedata.py @ONLY)

find_program(SWIG swig)
if(NOT SWIG)
  message("Cannot find swig. Please install swig program. Consult your distribution package.")
endif()

find_program(PYTHON python)
execute_process(COMMAND ${PYTHON} -c 'import sys; v = "%d.%d" % (ys.version_info[0], sys.version_inf[1]); print v'
  OUTPUT_VARIABLE PYTHON_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
set(PYTHON_INC_DIR /usr/include/python${PYTHON_VERSION})

set(IFILE ParameterClient)

add_library(_${IFILE} SHARED ${IFILE}_wrap.cxx)
add_custom_command(_${IFILE}
  DEPENDS ${IFILE}.h
  COMMAND ${SWIG} -c++ -python ${IFILE}.i
)

target_include_directories(_${IFILE} PRIVATE 
  ${CMAKE_SOURCE_DIR}/src/lib/SiTCP/CPP/Sock
  ${PYTHON_INC_DIR}
  )
target_link_directories( _${IFILE} PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/SiTCP/CPP/Sock)
target_link_libraries(_${IFILE} 
  Sock
  )

install(TARGETS
  _${IFILE}
  LIBRARY DESTINATION ${WWW_DOCUMENT_ROOT}/daqmw/operatorPanel
  )

install(FILES
  operatorPanel0.html
  ParameterClient.py
  daq.py
  writedata.py
  runNumber.txt
  DESTINATION ${WWW_DOCUMENT_ROOT}/daqmw/operatorPanel
  )

