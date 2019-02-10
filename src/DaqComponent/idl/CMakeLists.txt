file(COPY DAQService.idl         DESTINATION ${CMAKE_BINARY_DIR}/include/idl)
file(COPY DAQServiceSVC_impl.h   DESTINATION ${CMAKE_BINARY_DIR}/include/idl)
file(COPY DAQServiceSVC_impl.cpp DESTINATION ${CMAKE_BINARY_DIR}/include/idl)

install(FILES 
  DAQService.idl
  DAQServiceSVC_impl.cpp
  DAQServiceSVC_impl.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/idl
  )
