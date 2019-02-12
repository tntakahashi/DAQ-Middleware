add_executable(DaqOperatorComp 
  DaqOperator.cpp
  DaqOperatorComp.cpp
  ConfFileParser.cpp
  CreateDom.cpp
  )

target_include_directories(DaqOperatorComp
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/lib/SiTCP/CPP/Sock 
  ${CMAKE_BINARY_DIR}/src/mk
  ${OPENRTM_INCLUDE_DIRS}
  )

target_link_directories(DaqOperatorComp
  PUBLIC
  ${CMAKE_BINARY_DIR}/src/lib/SiTCP/CPP/Sock 
  ${CMAKE_BINARY_DIR}/src/mk
  ${OPENRTM_LIBRARY_DIRS}
  )

target_link_libraries(DaqOperatorComp
  DAQService
  Sock
  ${OPENRTM_LIBRARIES}
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
