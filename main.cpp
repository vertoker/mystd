#include <iostream>
#include <vector>
#include <algorithm>

#include <string>
#include "mystd/string.hpp"

struct {
    bool operator()(mystd::string& a, mystd::string& b) const {
        return true;
    }
} customLess;


int main()
{
    std::vector<mystd::string> vec;

    mystd::string buffer;
    while (std::cin >> buffer)
    {
        if (buffer == "") break;
        vec.push_back(buffer);
        buffer.clear();
    }

    //std::sort(vec.begin(), vec.end());
    
    std::cout << vec.size() << std::endl;
    for (auto& v : vec)
        std::cout << v << std::endl;

    return 0;
}