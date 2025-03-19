#include <stdio.h>
#include "checker.hpp"

int pass_counter = 0;
int fail_counter = 0;
void count_pass(const char* f, int line)
{
    pass_counter++;
}
void count_fail(const char* f, int line)
{
    fail_counter++;
    printf("FAILED in file: %s at line %d \n", f, line);
}
void test_result()
{
    printf("Test complete FAILS %d PASS %d of %d", fail_counter, pass_counter, pass_counter+fail_counter);
}