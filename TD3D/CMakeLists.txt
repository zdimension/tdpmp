cmake_minimum_required(VERSION 3.16)
project(TD3D)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(TD3D Dimension.hpp main.cpp Application.cpp)

target_link_libraries(TD3D ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})