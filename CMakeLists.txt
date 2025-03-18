cmake_minimum_required(VERSION 3.12.0)
project(mystd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

#set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}") # /inc
#set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}") # /src

#file(GLOB_RECURSE INCLUDES CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp")
#file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.c" "${SOURCE_DIR}/*.cpp")

#include_directories("${INCLUDE_DIR}")
#add_executable("${CMAKE_PROJECT_NAME}" "${INCLUDES}" "${SOURCES}")

add_executable("mystd" "main.cpp" "mystd/string.hpp" "mystd/string.cpp")

#include(CTest)
#enable_testing()
