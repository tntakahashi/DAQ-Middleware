add_library(sock-static STATIC sock.c)
add_library(sock        SHARED sock.c)

set(api_version 1)
set(patchlevel 0)
set(version "${api_version}.${patchlevel}")

set_target_properties(sock-static PROPERTIES OUTPUT_NAME sock CLEAN_DIRECT_OUTPUT 1)
set_target_properties(sock        PROPERTIES CLEAN_DIRECT_OUTPUT 1 VERSION ${version} SOVERSION ${api_version})

install(FILES sock.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS 
  sock-static 
  sock
  EXPORT DAQMW-export
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


