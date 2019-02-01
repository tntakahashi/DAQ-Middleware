install(PROGRAMS
  condition_xml2json  
  condition_xml2json.py 
  xml2json-with-attribute.xslt
  run.py  
  daqmw-rpm
  DESTINATION ${PROJECT_INSTALL_BINDIR}
  )

