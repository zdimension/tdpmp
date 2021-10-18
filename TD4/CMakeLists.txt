cmake_minimum_required(VERSION 3.16)
project(TD4)

set(CMAKE_CXX_STANDARD 20)
file(GLOB SRCS *.cpp)
add_executable(TD4 ${SRCS})
