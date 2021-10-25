cmake_minimum_required(VERSION 3.16)
project(TD5)

set(CMAKE_CXX_STANDARD 20)

add_executable(TD5 main.cpp Menu.cpp Menu.h WalkingMenu.cpp WalkingMenu.h MenuItem.cpp MenuItem.h SimpleMenuItem.cpp SimpleMenuItem.h)
