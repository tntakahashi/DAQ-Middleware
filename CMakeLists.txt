cmake_minimum_required(VERSION 2.6)

project(DAQ-Middleware)

set(RTM_ROOT $ENV{RTM_ROOT})

include(GNUInstallDirs)
set(CMAKE_INSTALL_PREFIX $ENV{CMAKE_INSTALL_PREFIX})
set(PROJECT_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
set(PROJECT_INSTALL_INCLUDEDIR ${PROJECT_INSTALL_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/daqmw) # xxx/include/daqmw
set(PROJECT_INSTALL_LIBDIR     ${PROJECT_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/daqmw)     # xxx/(lib,lib64)/daqmw
set(PROJECT_INSTALL_BINDIR     ${PROJECT_INSTALL_DIR}/${CMAKE_INSTALL_BINDIR}/daqmw)     # xxx/bin/daqmw
set(PROJECT_INSTALL_DATADIR    ${PROJECT_INSTALL_DIR}/${CMAKE_INSTALL_DATADIR}/daqmw)    # xxx/share/daqmw   

message("CMAKE_INSTALL_PREFIX:       ${CMAKE_INSTALL_PREFIX}")
message("PROJECT_INSTALL_DIR:        ${PROJECT_INSTALL_DIR}")
message("PROJECT_INSTALL_INCLUDEDIR: ${PROJECT_INSTALL_INCLUDEDIR}")
message("PROJECT_INSTALL_LIBDIR:     ${PROJECT_INSTALL_LIBDIR}")
message("PROJECT_INSTALL_BINDIR:     ${PROJECT_INSTALL_BINDIR}")
message("PROJECT_INSTALL_DATADIR:    ${PROJECT_INSTALL_DATADIR}")

# https://cmake.org/Wiki/CMake_RPATH_handling
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${PROJECT_INSTALL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-Wl,--enable-new-dtags")
    set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--enable-new-dtags")
    set(CMAKE_INSTALL_RPATH "${PROJECT_INSTALL_LIBDIR}")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_INSTALL_RPATH "@loader_path/../${PROJECT_INSTALL_LIBDIR}")
  else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_LIBDIR}")
  endif()
endif()


add_subdirectory(src)
add_subdirectory(bin)
#add_subdirectory(conf)
#add_subdirectory(docs)
#add_subdirectory(etc)
#add_subdirectory(examples)
#add_subdirectory(utils)
#add_subdirectory(www)


