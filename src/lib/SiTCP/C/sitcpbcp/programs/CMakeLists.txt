include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../sock
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  )

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/../../sock
  ${CMAKE_CURRENT_BINARY_DIR}/../
  )

add_executable(readReg readReg.c)
target_link_libraries(readReg sitcpbcp sock)

add_executable(writeReg writeReg.c)
target_link_libraries(writeReg sitcpbcp sock)

# install(TARGETS readReg writeReg
#   RUNTIME DESTINATION ${PROJECT_INSTALL_BINDIR}
#   )
