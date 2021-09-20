cmake_minimum_required(VERSION 3.16)
project(TD3)

set(CMAKE_CXX_STANDARD 14)

add_executable(TD3 main.cpp Node.ipp Tree.ipp)
