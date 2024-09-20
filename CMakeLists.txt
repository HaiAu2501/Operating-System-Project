cmake_minimum_required(VERSION 3.10.2)

project(Operating-System-Project VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

add_executable(Operating-System-Project main.cpp)
add_definitions(-DNOMINMAX)

install(TARGETS Operating-System-Project RUNTIME DESTINATION .)

add_subdirectory(Process)

install(DIRECTORY Testcase/ DESTINATION Testcase FILES_MATCHING PATTERN "*")

install(DIRECTORY Document/ DESTINATION Document FILES_MATCHING PATTERN "*")