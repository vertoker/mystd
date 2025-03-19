#pragma once
#include <iostream>

void count_pass(const char* f, int line);
void count_fail(const char* f, int line);
void test_result();
#define CHECK(cond1, cond2) \
    do { \
        if (cond1 == cond2) { \
            count_pass(__FILE__, __LINE__); \
        } else { \
            std::cout << "CHECK Failed cond1: " << cond1 << " cond2: " << cond2 << std::endl; \
            count_fail(__FILE__, __LINE__); \
        } \
    } while (0);
