include(${CMAKE_SOURCE_DIR}/www/Distributions.cmake)

install(FILES
  daq.js
  prototype.js
  DESTINATION ${WWW_DOCUMENT_ROOT}/daqmw/js
  )
