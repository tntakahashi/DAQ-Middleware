include(${CMAKE_SOURCE_DIR}/www/Distributions.cmake)

set(PROG conditionPanel.py)

if(USE_MOD_WSGI)
  set(URL "http://localhost/daqmw/scripts/daq.py/")
elseif(USE_MOD_PYTHON)
  set(URL "http://localhost/daqmw/operatorPanel/daq.py/")
endif()

configure_file(${PROG}.in ${PROG} @ONLY)

install(PROGRAMS ${PROG} DESTINATION ${CMAKE_INSTALL_BINDIR})

