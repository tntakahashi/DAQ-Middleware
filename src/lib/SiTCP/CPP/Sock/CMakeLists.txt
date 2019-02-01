add_library(Sock-static STATIC Sock.cpp)
add_library(Sock-shared SHARED Sock.cpp)

set(api_version 1)
set(patchlevel 0)
set(version "${api_version}.${patchlevel}")

set_target_properties(Sock-static PROPERTIES OUTPUT_NAME Sock CLEAN_DIRECT_OUTPUT 1)
set_target_properties(Sock-shared PROPERTIES OUTPUT_NAME Sock CLEAN_DIRECT_OUTPUT 1 VERSION ${version} SOVERSION ${api_version})

install(FILES Sock.h DESTINATION ${PROJECT_INSTALL_INCLUDEDIR})
install(TARGETS Sock-static Sock-shared
  ARCHIVE DESTINATION ${PROJECT_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
  )


add_subdirectory(test)
