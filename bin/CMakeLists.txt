configure_file(run.py.in run.py @ONLY)

install(PROGRAMS
  condition_xml2json  
  condition_xml2json.py 
  xml2json-with-attribute.xslt
  ${CMAKE_CURRENT_BINARY_DIR}/run.py  
  daqmw-rpm
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

