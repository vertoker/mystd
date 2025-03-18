#pragma once
#include <iostream>

namespace mystd
{
    class string
    {
    public:
        // I decided to use growth factor identical to std::string
        // I know it's less efficient in most cases, but who cares
        static constexpr double GrowthFactor = 2.0;

        string();
        string(const char* c_str);
        
        // rule of 5
        string(const string& other);
        string(string&& other) noexcept;
        string& operator=(const string& other);
        string& operator=(string&& other) noexcept;
        ~string();

        // operators
	    inline char& operator[](size_t index) const { return _data[index]; }

        friend bool operator==(const string& lhs, const string& rhs) noexcept;
        friend bool operator==(const string& lhs, const char* rhs);
        friend bool operator!=(const string& lhs, const string& rhs) noexcept;
        friend bool operator!=(const string& lhs, const char* rhs);

        friend string operator+(const string& lhs, const string& rhs);
        friend string operator+(const string& lhs, const char* rhs);

        void operator+=(const string& other);
        void operator+=(const char* other);

        friend std::istream& operator>>(std::istream& is, string& str);
        friend std::ostream& operator<<(std::ostream& os, string& str);

        // "fields"
        inline size_t      size() const noexcept { return _size; }
        inline size_t      capacity() const noexcept { return _capacity; }
        inline const char* data() const { return _data; }

        // functions
        void reserve(const size_t newCapacity);
        void resize(const size_t newSize, const char defaultChar);
        void push_back(char character);
        void clear() noexcept;
        
    private:
        size_t UnusedCapacity()  const { return _capacity - _size; }
        size_t GetNextCapacity() const { return _capacity == 0 ? 1 : (size_t)((double)_capacity * GrowthFactor); }

        // 1. _size and _capacity declared only valid bytes, they both EXCLUDE null-terminated last byte
        // This also means real allocated bytes ALWAYS equals _capacity + 1
        // 2. order here used in memory of class, this better order

        size_t _size;
        size_t _capacity;
        char* _data;
    };

    // External operators
    bool operator==(const string& lhs, const string& rhs) noexcept;
    bool operator==(const string& lhs, const char* rhs);
    bool operator!=(const string& lhs, const string& rhs) noexcept;
    bool operator!=(const string& lhs, const char* rhs);

    string operator+(const string& lhs, const string& rhs);
    string operator+(const string& lhs, const char* rhs);

    std::istream& operator>>(std::istream& is, string& str);
    std::ostream& operator<<(std::ostream& os, string& str);
    
} // namespace mystd
