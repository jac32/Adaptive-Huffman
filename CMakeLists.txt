cmake_minimum_required(VERSION 3.1.0)
set (CMAKE_CXX_STANDARD 11)

project(Adaptive-Huffman)
include_directories(inc)
file(GLOB SOURCES "src/*.cpp")
add_executable(huff ${SOURCES})
