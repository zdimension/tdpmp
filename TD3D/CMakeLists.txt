cmake_minimum_required(VERSION 3.16)
project(TD3D)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(TD3D primitives/Dimension.hpp main.cpp Application.cpp entities/Cube.cpp entities/Cube.hpp primitives/Vector3d.hpp primitives/Color.hpp scenes/Scene.cpp scenes/Scene.hpp entities/Entity.hpp scenes/RotatingCubes.hpp scenes/Orbits.hpp)

include_directories(${OPENGL_INCLUDE_DIRS} ${SDL_INCLUDE_DIRS})
target_link_libraries(TD3D ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})