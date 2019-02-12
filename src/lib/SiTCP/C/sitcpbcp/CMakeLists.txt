include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sock)

add_library(sitcpbcp-static STATIC sitcpbcp.c)
add_library(sitcpbcp        SHARED sitcpbcp.c)

set(api_version 1)
set(patchlevel 0)
set(version "${api_version}.${patchlevel}")

set_target_properties(sitcpbcp-static PROPERTIES OUTPUT_NAME sitcpbcp CLEAN_DIRECT_OUTPUT 1)
set_target_properties(sitcpbcp        PROPERTIES CLEAN_DIRECT_OUTPUT 1 VERSION ${version} SOVERSION ${api_version})

install(FILES sitcpbcp.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS 
  sitcpbcp-static 
  sitcpbcp
  EXPORT DAQMW-export
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDE_DIR}
  PUBLIC_HAEDER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


add_subdirectory(programs)
