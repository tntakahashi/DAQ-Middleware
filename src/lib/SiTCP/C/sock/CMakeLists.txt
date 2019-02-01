add_library(sock-static STATIC sock.c)
add_library(sock-shared SHARED sock.c)

set(api_version 1)
set(patchlevel 0)
set(version "${api_version}.${patchlevel}")

set_target_properties(sock-static PROPERTIES OUTPUT_NAME sock CLEAN_DIRECT_OUTPUT 1)
set_target_properties(sock-shared PROPERTIES OUTPUT_NAME sock CLEAN_DIRECT_OUTPUT 1 VERSION ${version} SOVERSION ${api_version})

install(FILES sock.h DESTINATION ${PROJECT_INSTALL_INCLUDEDIR})
install(TARGETS sock-static sock-shared
  ARCHIVE DESTINATION ${PROJECT_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
  )

