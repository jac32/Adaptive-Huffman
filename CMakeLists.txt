cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR Adaptive-Huffman)
set(CMAKE_BUILD_TYPE Release)
project(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)
add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++11 -O3)

#-------------------
# set common include folder for module
#-------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/inc)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#-------------------
# Module source
#-------------------
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)

include_directories(${COMMON_INCLUDES})
file(GLOB SRC_LIB_FILES ${PROJECT_SOURCE_DIR}/src/lib/*.cc)
add_library(${PROJECT_LIB_NAME} ${SRC_LIB_FILES})
add_executable(huff ${PROJECT_SOURCE_DIR}/src/main.cc ${SRC_LIB_FILES})
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

#-------------------
# Test
#-------------------
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cc)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)


target_link_libraries(${PROJECT_TEST_NAME}
  ${GTEST_LIBS_DIR}/libgtest.a
  ${GTEST_LIBS_DIR}/libgtest_main.a
  ${PROJECT_LIB_NAME}
  )

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_test(tests ${PROJECT_TEST_NAME})
