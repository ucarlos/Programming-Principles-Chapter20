cmake_minimum_required(VERSION 3.15)
project(Chapter20)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chapter20_02 Chapter20_02.cc)
target_link_libraries(Chapter20_02 stdc++fs)

add_executable(Chapter20_06 Chapter20_06.cc)
add_executable(Chapter20_07 Chapter20_07.cc)
add_executable(Chapter20_09 Chapter20_09.cc)
add_executable(Chapter20_12 Chapter20_12.cc)
target_link_libraries(Chapter20_07 stdc++fs)
target_link_libraries(Chapter20_09 stdc++fs)
