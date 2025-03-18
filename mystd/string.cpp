#include "string.hpp"

#include "string.h"

using mystd::string;

// Yes, in any default ctor, it allocate 1 byte, SSO here is required
string::string() : _size{0}, _capacity{0}, _data{new char[1]()} { }

string::string(const char* c_str)
{
    _capacity = strlen(c_str);
    _size = _capacity;
    _data = new char[_capacity + 1];

    // everywhere uses memcpy instead of strcpy, because in all cases I know _size
    // If you prefer (maybe) strcpy or strcpy_s, change it yourself
    memcpy(_data, c_str, _capacity + 1);
}

string::~string()
{
    delete[] _data;
}

string::string(const string& other) : _size{other._size}, _capacity{other._capacity}
{
    _data = new char[_capacity + 1];
    // everywhere, I use _size (if available) because only ACTIVE string
    // must end with null-terminated char, last allocated byte is not necessary
    // It optimize cases when
    memcpy(_data, other._data, _size + 1);
}
string::string(string&& other) noexcept : _size{other._size}, _capacity{other._capacity}, _data{other._data}
{
    _size = 0;
    _capacity = 0;
    _data = nullptr;
}

string& string::operator=(const string& other)
{
    if (this == &other) return *this;

    delete[] _data;

    _size = other._size;
    _capacity = other._capacity;
    _data = new char[_capacity + 1];
    memcpy(_data, other._data, _size + 1);

    return *this;
}
string& string::operator=(string&& other) noexcept
{
    if (this == &other) return *this;

    delete[] _data;

    _size = other._size;
    _capacity = other._capacity;
    _data = other._data;

    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;

    return *this;
}


void string::reserve(const size_t newCapacity)
{
    if (newCapacity <= _capacity) return;

    char* newData = new char[newCapacity + 1];
    if (_data != nullptr)
    {
        memcpy(newData, _data, _size + 1);
        delete[] _data;
    }

    _capacity = newCapacity;
    _data = newData;
}
void string::resize(const size_t newSize, const char defaultChar)
{
    if (newSize <= _size) return;

    if (newSize > _capacity)
        // it's a mess with 3 choices of behaviour
        reserve((newSize < _capacity * string::GrowthFactor) ? GetNextCapacity() : newSize);
    
    memset(_data + _size, defaultChar, newSize - _size);
    _size = newSize;
    _data[_size - 1] = 0;
}
void string::push_back(char character)
{
    if (UnusedCapacity() == 0)
        reserve(GetNextCapacity());
    
    _data[_size] = character;
    _data[++_size] = 0;
}
void string::clear() noexcept
{
    memset(_data, 0, _capacity);
    _size = 0;
}

bool mystd::operator==(const string& lhs, const string& rhs) noexcept
{
    if (lhs._size != rhs._size) return false;

    for (size_t i = 0; i < lhs._size; i++)
        if (lhs[i] != rhs[i]) return false;
    return true;
}
bool mystd::operator==(const string& lhs, const char* rhs)
{
    //if (lhs._size != strlen(rhs)) return false;

    size_t i = 0;
    for (; i < lhs._size; i++)
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
    char* newData = new char[lhs._size + rhs._size];
    
    memcpy(newData, lhs._data, lhs._size);
    memcpy(newData + lhs._size, rhs._data, rhs._size);

    string result(newData);
    delete[] newData;

    return result;
}
string mystd::operator+(const string& lhs, const char* rhs)
{
    size_t rhsSize = strlen(rhs);
    char* newData = new char[lhs._size + rhsSize];
    
    memcpy(newData, lhs._data, lhs._size);
    memcpy(newData + lhs._size, rhs, rhsSize);

    string result(newData);
    delete[] newData;

    return result;
}

void mystd::string::operator+=(const string& other)
{
    size_t newSize = _size + other._size;
    if (newSize < _capacity) reserve(newSize);
    memcpy(_data + _size, other._data, other._size);
}
void mystd::string::operator+=(const char* other)
{
    size_t otherSize = strlen(other);
    size_t newSize = _size + otherSize;
    if (newSize < _capacity) reserve(newSize);
    memcpy(_data + _size, other, otherSize);
}

std::istream& mystd::operator>>(std::istream& is, string& str)
{
    char temp;
    is.get(temp);

    while (temp != '\n')
    {
        str.push_back(temp);
        is.get(temp);
    }

    return is;
}
std::ostream& mystd::operator<<(std::ostream& os, string& str)
{
    for (size_t i = 0; i < str._size; i++)
        os << str[i];
    return os;
}
