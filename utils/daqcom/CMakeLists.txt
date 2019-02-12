set(PYTHON_SITELIB "${CMAKE_INSTALL_LIBDIR}/python")

install(PROGRAMS 
  daqcom
  DESTINATION ${PYTHON_SITELIB}
  )

install(TARGETS
  daqmwcom.py
  LIBRARY DESTINATION ${PYTHON_SITELIB}
  )

install(TARGETS
  httplib2/__init__.py
  httplib2/iri2uri.py
  httplib2/cacerts.txt
  httplib2/socks.py
  LIBRARY DESTINATION ${PYTHON_SITELIB}/httplib2
  )

  
