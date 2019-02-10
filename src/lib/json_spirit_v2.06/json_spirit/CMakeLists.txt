set(cppsrcs 
  json_spirit_reader.cpp
  json_spirit_value.cpp
  json_spirit_writer.cpp
  )

add_library(JsonSpirit-static STATIC ${cppsrcs})
add_library(JsonSpirit-shared SHARED ${cppsrcs})

set_target_properties(JsonSpirit-static PROPERTIES OUTPUT_NAME JsonSpirit CLEAN_DIRECT_OUTPUT 1)
set_target_properties(JsonSpirit-shared PROPERTIES OUTPUT_NAME JsonSpirit CLEAN_DIRECT_OUTPUT 1)

install(TARGETS
  JsonSpirit-static
  JsonSpirit-shared
  EXPORT DAQMW-export
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

# install(EXPORT DAQMW-export
#   FILE DAQMW-config.cmake
#   DESTINATION ${CMAKE_INSTALL_DATA_DIR}/cmake
#   )
