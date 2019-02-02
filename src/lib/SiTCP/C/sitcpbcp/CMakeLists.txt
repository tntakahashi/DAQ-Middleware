include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sock)

add_library(sitcpbcp-static STATIC sitcpbcp.c)
add_library(sitcpbcp-shared SHARED sitcpbcp.c)

set(api_version 1)
set(patchlevel 0)
set(version "${api_version}.${patchlevel}")

set_target_properties(sitcpbcp-static PROPERTIES OUTPUT_NAME sitcpbcp CLEAN_DIRECT_OUTPUT 1)
set_target_properties(sitcpbcp-shared PROPERTIES OUTPUT_NAME sitcpbcp CLEAN_DIRECT_OUTPUT 1 VERSION ${version} SOVERSION ${api_version})

install(FILES sitcpbcp.h DESTINATION ${PROJECT_INSTALL_INCLUDEDIR})
install(TARGETS sitcpbcp-static sitcpbcp-shared
  ARCHIVE DESTINATION ${PROJECT_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
  )

add_subdirectory(programs)
