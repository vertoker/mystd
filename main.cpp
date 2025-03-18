#include <iostream>
#include <utility>
#include <vector>

#include <string>
#include "string.hpp"

int main()
{
    std::vector<mystd::string> vec;

    mystd::string buffer;

    while (std::cin >> buffer)
    {
        if (buffer == "") break;
        vec.push_back(buffer);
        std::cout << buffer << std::endl;
        buffer.Clear();
    }
    
    std::cout << vec.size() << std::endl;
    for (auto& v : vec)
        std::cout << v << std::endl;

    return 0;
}