
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -g -pipe -O2 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")

add_subdirectory(SiTCP)
add_subdirectory(json_spirit_v2.06)




