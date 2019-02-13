add_library(Sock-static STATIC Sock.cpp)
add_library(Sock        SHARED Sock.cpp)

set(api_version 1)
set(patchlevel 0)
set(version "${api_version}.${patchlevel}")

set_target_properties(Sock-static PROPERTIES OUTPUT_NAME Sock CLEAN_DIRECT_OUTPUT 1)
set_target_properties(Sock        PROPERTIES CLEAN_DIRECT_OUTPUT 1 VERSION ${version} SOVERSION ${api_version})

install(FILES Sock.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS 
  Sock-static 
  Sock
  EXPORT DAQMWTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

#add_subdirectory(test)
