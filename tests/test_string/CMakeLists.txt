
add_executable(test_string main.cpp mystd ${TEST_SOURCES})
target_include_directories(test_string PUBLIC ${TEST_INCLUDE_DIRS})

add_test(test_string, test_string)
