
set(TEST_SOURCES "checker.hpp" "checker.cpp")
set(TEST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/mystd ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_subdirectory(test_string)
add_subdirectory(test_array)
