cmake_minimum_required(VERSION 2.9)

#projet declaration
project(CellularAutomata)

#define platform independent variables
SET(GCC_COMPILE_FLAGS "-g -ansi -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -D_DEBUG_ -std=c++17")
SET(GCC_LINK_FLAGS    "")

#add flags to the compiler
add_definitions(${GCC_COMPILE_FLAGS}) 


SET(ALL_SRC_FILES "main.cpp")
find_package(SFML COMPONENTS graphics window system)
#executable definition
add_executable(

        cellularAutomata

        ${ALL_SRC_FILES}

)
if (SFML_FOUND)
    add_compile_definitions(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cellularAutomata sfml-graphics sfml-system)
endif()

add_executable(palindrome main_palindrome.cpp)