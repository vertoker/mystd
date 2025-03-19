#include <iostream>
#include <vector>
#include <algorithm>

#include <string>
#include "string.hpp"

struct {
    bool operator()(mystd::string& a, mystd::string& b) const {
        size_t minSize = (a.size() < b.size()) ? a.size() : b.size();
    
        for (int i = 0; i < minSize; ++i)
        {
            if (tolower(a[i]) > tolower(b[i])) return true;
            if (tolower(a[i]) < tolower(b[i])) return false;
        }
        return a.size() > b.size();
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

    std::sort(vec.begin(), vec.end(), customLess);
    
    std::cout << vec.size() << std::endl;
    for (auto& v : vec)
        std::cout << v << std::endl;

    return 0;
}