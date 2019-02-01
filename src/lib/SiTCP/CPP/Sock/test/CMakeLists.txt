include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/../)

add_executable(socktest socktest.cpp)
target_link_libraries(socktest Sock)

add_executable(socktestexception socktestexception)
target_link_libraries(socktestexception Sock)
