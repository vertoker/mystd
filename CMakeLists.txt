cmake_minimum_required(VERSION 3.10.0)
project(mystd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(SOURCES "main.cpp" "mystd/string.hpp" "mystd/string.cpp")
add_executable("mystd" "main.cpp" "mystd/string.hpp" "mystd/string.cpp")

#include(CTest)
#enable_testing()
#add_subdirectory(tests)
