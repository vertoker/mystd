#include "string.hpp"
#include <string.h>

using mystd::string;

string::string() : size{0}, capacity{0}, data{new char[1]} { }

string::string(const char* c_str)
{
    capacity = strlen(c_str);
    size = capacity;
    data = new char[capacity + 1];
    strcpy(data, c_str);
    //memcpy(data, c_str, capacity);
}

string::~string()
{
    delete[] data;
}

string::string(const string& other) : size{other.size}, capacity{other.capacity}
{
    data = new char[capacity + 1];
    strcpy(data, other.data);
    //memcpy(data, other.data, size);
    std::cout << "copy ctor" << std::endl;
}
string::string(string&& other) noexcept : size{other.size}, capacity{other.capacity}, data{other.data}
{
    size = 0;
    capacity = 0;
    data = nullptr;
}

string& string::operator=(const string& other)
{
    if (this == &other) return *this;

    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = new char[capacity + 1];
    strcpy(data, other.data);
    //memcpy(data, other.data, size);

    return *this;
}
string& string::operator=(string&& other) noexcept
{
    if (this == &other) return *this;

    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = other.data;

    other.size = 0;
    other.capacity = 0;
    other.data = nullptr;

    return *this;
}


void string::Reserve(const size_t newCapacity)
{
    if (newCapacity <= capacity) return;

    char* newData = new char[newCapacity];
    if (data != nullptr)
    {
        memcpy(newData, data, size);
        delete[] data;
    }

    capacity = newCapacity;
    data = newData;
}
void string::Resize(const size_t newSize)
{
    if (newSize <= size) return;

    if (newSize > capacity)
        Reserve((newSize < capacity * 2) ? GetGrowthFactor() : newSize);
    
    memset(data + size, 0, newSize - size + 1);
    size = newSize;
}
void string::PushBack(char character)
{
    if (UnusedCapacity() == 0)
        Reserve(GetGrowthFactor());
    
    data[size] = character;
    data[++size] = 0;
}
void string::Clear() noexcept
{
    memset(data, 0, capacity);
    size = 0;
}

bool mystd::operator==(const string& lhs, const string& rhs) noexcept
{
    if (lhs.size != rhs.size) return false;

    for (size_t i = 0; i < lhs.size; i++)
        if (lhs[i] != rhs[i]) return false;
    return true;
}
bool mystd::operator==(const string& lhs, const char* rhs)
{
    //if (lhs.size != strlen(rhs)) return false;

    size_t i = 0;
    for (; i < lhs.size; i++)
    {
        if (!rhs[i] || // if lhs > rhs
            lhs[i] != rhs[i]) return false;
    }
    return !rhs[i]; // if lhs < rhs
}

bool mystd::operator!=(const string& lhs, const string& rhs) noexcept
{
    return !(lhs == rhs);
}
bool mystd::operator!=(const string& lhs, const char* rhs)
{
    return !(lhs == rhs);
}

string mystd::operator+(const string& lhs, const string& rhs)
{
    char* newData = new char[lhs.size + rhs.size];
    
    memcpy(newData, lhs.data, lhs.size);
    memcpy(newData + lhs.size, rhs.data, rhs.size);

    string result(newData);
    delete[] newData;

    return result;
}
string mystd::operator+(const string& lhs, const char* rhs)
{
    size_t rhsSize = strlen(rhs);
    char* newData = new char[lhs.size + rhsSize];
    
    memcpy(newData, lhs.data, lhs.size);
    memcpy(newData + lhs.size, rhs, rhsSize);

    string result(newData);
    delete[] newData;

    return result;
}

void mystd::string::operator+=(const string& other)
{
    size_t newSize = size + other.size;
    if (newSize < capacity) Reserve(newSize);
    memcpy(data + size, other.data, other.size);
}
void mystd::string::operator+=(const char* other)
{
    size_t otherSize = strlen(other);
    size_t newSize = size + otherSize;
    if (newSize < capacity) Reserve(newSize);
    memcpy(data + size, other, otherSize);
}

std::istream& mystd::operator>>(std::istream& is, string& str)
{
    char temp;
    is.get(temp);

    while (temp != '\n')
    {
        str.PushBack(temp);
        is.get(temp);
    }

    return is;
}
std::ostream& mystd::operator<<(std::ostream& os, string& str)
{
    for (size_t i = 0; i < str.size; i++)
        os << str[i];
    return os;
}
