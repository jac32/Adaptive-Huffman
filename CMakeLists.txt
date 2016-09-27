cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

project(directory_test)
include_directories(inc)
file(GLOB SOURCES "src/*.cpp")
add_executable(huff ${SOURCES})
