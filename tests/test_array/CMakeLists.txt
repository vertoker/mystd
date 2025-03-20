
add_executable(test_array main.cpp mystd ${TEST_SOURCES})
target_include_directories(test_array PUBLIC ${TEST_INCLUDE_DIRS})

add_test(test_array, test_array)
