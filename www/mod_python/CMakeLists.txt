include(${CMAKE_SOURCE_DIR}/www/Distributions.cmake)

add_subdirectory(js)
add_subdirectory(operatorPanel)
add_subdirectory(parts)

configure_file(daq.conf.in daq.conf @ONLY)

install(FILES
  daq.conf DESTINATION ${HTTPD_CONF_DIR}
  )
