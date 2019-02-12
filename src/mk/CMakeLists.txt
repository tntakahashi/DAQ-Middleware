install(FILES comp.mk DESTINATION ${CMAKE_INSTALL_DATADIR}/mk)

#-------------------------------------------------------------------------------
# libDAQService
#-------------------------------------------------------------------------------
set(srcs DAQServiceSkel.cpp DAQServiceSVC_impl.cpp)
add_library(DAQService-static STATIC ${srcs})
add_library(DAQService        SHARED ${srcs})


add_custom_command(
 OUTPUT DAQService.hh DAQServiceSK.cc DAQServiceDynSK.cc DAQServiceSkel.h DAQServiceStub.h DAQServiceSkel.cpp DAQServiceStub.cpp DAQServiceSVC_impl.cpp
 COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/DaqComponent/idl/DAQService.idl         ${CMAKE_CURRENT_BINARY_DIR}/DAQService.idl
 COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/DaqComponent/idl/DAQServiceSVC_impl.h   ${CMAKE_CURRENT_BINARY_DIR}/DAQServiceSVC_impl.h
 COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/DaqComponent/idl/DAQServiceSVC_impl.cpp ${CMAKE_CURRENT_BINARY_DIR}/DAQServiceSVC_impl.cpp
 COMMAND ${OPENRTM_IDLC} ${OPENRTM_IDLFLAGS} -I${OPENRTM_INCLUDE_DIR}/rtm/idl ${CMAKE_CURRENT_BINARY_DIR}/DAQService.idl
 COMMAND ${OPENRTM_IDL_WRAPPER} ${OPENRTM_IDL_WRAPPER_FLAGS} --idl-file=${CMAKE_CURRENT_BINARY_DIR}/DAQService.idl
 )

set_target_properties(DAQService-static PROPERTIES OUTPUT_NAME DAQService CLEAN_DIRECT_OUTPUT 1)
set_target_properties(DAQService        PROPERTIES CLEAN_DIRECT_OUTPUT 1)

foreach(var DAQService-static DAQService)
  target_include_directories(${var}
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${OPENRTM_INCLUDE_DIRS}
    )
  target_link_directories(${var}
    PUBLIC
    ${OPENRTM_LIBRARY_DIRS}
    )
  target_link_libraries(${var} 
    ${OPENRTM_LIBRARIES}
    )
endforeach(var)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/DAQService.hh 
  ${CMAKE_CURRENT_BINARY_DIR}/DAQServiceSkel.h
  ${CMAKE_CURRENT_BINARY_DIR}/DAQServiceStub.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

install(TARGETS
  DAQService-static
  DAQService
  EXPORT DAQMW-export
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


