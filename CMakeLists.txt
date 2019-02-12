cmake_minimum_required(VERSION 2.6)

project(DAQMW)

#set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

find_package(OpenRTM REQUIRED)

set(CMAKE_INSTALL_PREFIX $ENV{CMAKE_INSTALL_PREFIX})
include(GNUInstallDirs)
message("CMAKE_INSTALL_PREFIX:     ${CMAKE_INSTALL_PREFIX}")
message("CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")
message("CMAKE_INSTALL_LIBDIR:     ${CMAKE_INSTALL_LIBDIR}")
message("CMAKE_INSTALL_BINDIR:     ${CMAKE_INSTALL_BINDIR}")
message("CMAKE_INSTALL_DATADIR:    ${CMAKE_INSTALL_DATADIR}")


# https://cmake.org/Wiki/CMake_RPATH_handling
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-Wl,--enable-new-dtags")
    set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--enable-new-dtags")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
  else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  endif()
endif()


add_subdirectory(src)
add_subdirectory(bin)
add_subdirectory(conf)
add_subdirectory(docs)
add_subdirectory(etc)
add_subdirectory(examples)
#add_subdirectory(utils)
#add_subdirectory(www)

install(EXPORT DAQMW-export
  FILE DAQMW-config.cmake
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake
  )

