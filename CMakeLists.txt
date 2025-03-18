cmake_minimum_required(VERSION 3.10.0)
project(mystd LANGUAGES C CXX)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}") # /inc
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}") # /src

file(GLOB_RECURSE INCLUDES CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.c" "${SOURCE_DIR}/*.cpp")

include_directories("${INCLUDE_DIR}")
add_executable("${CMAKE_PROJECT_NAME}" "${INCLUDES}" "${SOURCES}")

include(CTest)
enable_testing()
