cmake_minimum_required(VERSION 3.16)
project(TD4)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC1 spec1/*.cpp)
file(GLOB SRC2 spec2/*.cpp)

add_executable(TD4_1 ${SRC1})
add_executable(TD4_2 ${SRC2})
