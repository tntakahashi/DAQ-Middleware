cmake_minimum_required(VERSION 2.6)

project(DAQMW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

file(READ ${CMAKE_SOURCE_DIR}/VERSION versionstr)
string(STRIP ${versionstr} versionstr)
string(REGEX REPLACE "([0-9]+)[.][0-9]+[.][0-9]+" "\\1" DAQMW_MAJOR_VERSION ${versionstr})
string(REGEX REPLACE "[0-9]+[.]([0-9]+)[.][0-9]+" "\\1" DAQMW_MINOR_VERSION ${versionstr})
string(REGEX REPLACE "[0-9]+[.][0-9]+[.]([0-9]+)" "\\1" DAQMW_PATCH_VERSION ${versionstr})
set(DAQMW_VERSION "${DAQMW_MAJOR_VERSION}.${DAQMW_MINOR_VERSION}.${DAQMW_PATCH_VERSION}")
set(PROJECT_VERSION ${DAQMW_VERSION})

message("DAQMW_VERSION:       ${DAQMW_VERSION}")
message("DAQMW_MAJOR_VERSION: ${DAQMW_MAJOR_VERSION}")
message("DAQMW_MINOR_VERSION: ${DAQMW_MINOR_VERSION}")
message("DAQMW_PATCH_VERSION: ${DAQMW_PATCH_VERSION}")


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

#-------------------------------------------------------------------------------
# package config
#-------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
set(ConfigPackageLocation lib/cmake/DAQMW-${DAQMW_VERSION})
export(EXPORT DAQMWTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/DAQMW/DAQMWTargets.cmake"
  NAMESPACE DAQMW::
)


configure_package_config_file(cmake/DAQMWConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/DAQMW/DAQMWConfig.cmake"
  INSTALL_DESTINATION ${ConfigPackageLocation}
  PATH_VARS CMAKE_INSTALL_PREFIX CMAKE_INSTALL_BINDIR CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_DATADIR
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DAQMW/DAQMWConfigVersion.cmake"
  VERSION ${DAQMW_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(EXPORT DAQMWTargets
  FILE DAQMWTargets.cmake
  NAMESPACE DAQMW::
  DESTINATION ${ConfigPackageLocation}
  )
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/DAQMW/DAQMWConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/DAQMW/DAQMWConfigVersion.cmake"
  DESTINATION ${ConfigPackageLocation}
  COMPONENT Devel
)

