set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

add_custom_command(
 OUTPUT DAQService.hh DAQServiceSK.cc DAQServiceDynSK.cc DAQServiceSkel.h DAQServiceStub.h DAQServiceSkel.cpp DAQServiceStub.cpp 
 DEPENDS ${CMAKE_BINARY_DIR}/include/idl/DAQService.idl
 COMMAND ${OPENRTM_IDLC} ${OPENRTM_IDLFLAGS} -I${OPENRTM_INCLUDE_DIR}/rtm/idl ${CMAKE_BINARY_DIR}/include/idl/DAQService.idl
 COMMAND ${OPENRTM_IDL_WRAPPER} ${OPENRTM_IDL_WRAPPER_FLAGS} --idl-file=${CMAKE_BINARY_DIR}/include/idl/DAQService.idl
 )

add_executable(DaqOperatorComp 
  DaqOperator.cpp
  DaqOperatorComp.cpp
  ConfFileParser.cpp
  CreateDom.cpp
  DAQService.hh
  DAQServiceSkel.cpp
  ${CMAKE_BINARY_DIR}/include/idl/DAQServiceSVC_impl.cpp
  )

target_include_directories(DaqOperatorComp
  PRIVATE
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_BINARY_DIR}/include/idl
  ${CMAKE_CURRENT_BINARY_DIR}
  ${OPENRTM_INCLUDE_DIRS}
  )

target_link_directories(DaqOperatorComp
  PUBLIC
  ${OPENRTM_LIBRARY_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}/../lib/SiTCP/CPP/Sock 
  )

target_link_libraries(DaqOperatorComp
  ${OPENRTM_LIBRARIES}
  Sock
  xerces-c
)

install(FILES
  ComponentInfoContainer.h
  ConfFileParser.cpp
  ConfFileParser.h
  CreateDom.cpp
  CreateDom.h
  DaqOperator.cpp
  DaqOperator.h
  DaqOperatorComp.cpp
  Parameter.h
  ParameterServer.h
  callback.h
  DESTINATION ${CMAKE_INSTALL_DATADIR}/DaqOperator
  )

install(FILES
  Makefile.in
  DESTINATION libexec 
  RENAME Makefile
  )

install(TARGETS
  DaqOperatorComp
  RUNTIME DESTINATION libexec
  )
