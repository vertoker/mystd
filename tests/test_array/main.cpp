#include <iostream>
#include <algorithm>

#include <array>
#include <string>

#include "mystd/array.hpp"
#include "mystd/string.hpp"

int main()
{
    mystd::array<mystd::string, 32> arr;
    std::array<std::string, 32> arr2;
    
    size_t counter = 1;
    for (auto& str : arr) {
        str = std::to_string(counter).data();
        ++counter;
    }
    
    for (auto it = arr.begin(); it != arr.end(); ++it)
        std::cout << *it << ' ';
    
    return 0;
}