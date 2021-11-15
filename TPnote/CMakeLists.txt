cmake_minimum_required(VERSION 3.16)
project(TPnote)

set(CMAKE_CXX_STANDARD 11)

add_executable(TPnote main.cpp Cinema.cpp Cinema.h Siege.h Client.h Personne.h ClientAbonne.h ClientOccasionnel.h CinemaException.h TestUtils.h)
