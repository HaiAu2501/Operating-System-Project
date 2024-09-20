cmake_minimum_required(VERSION 3.10.2)

project(Operating-System-Project VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Operating-System-Project main.cpp)
add_definitions(-DNOMINMAX)