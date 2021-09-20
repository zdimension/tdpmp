cmake_minimum_required(VERSION 3.16)
project(TD2)

set(CMAKE_CXX_STANDARD 20)

add_executable(TD2 main.cpp Gender.h Person.cpp Person.h PoliceRecord.cpp PoliceRecord.h Gender.cpp HealthInsuranceOffice.cpp HealthInsuranceOffice.h HealthID.cpp HealthID.h)
