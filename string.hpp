// string.hpp

#ifndef STRING_VERTOKER_H
#define STRING_VERTOKER_H

#include <iostream>

namespace mystd
{
    class string
    {
    public:
        string();
        string(const char* c_str);
        
        // rule of 5
        string(const string& other);
        string(string&& other) noexcept;
        string& operator=(const string& other);
        string& operator=(string&& other) noexcept;
        ~string();

        // operators
	    inline char& operator[](size_t index) const { return data[index]; }

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
        inline size_t      GetSize() const noexcept { return size; }
        inline size_t      GetCapacity() const noexcept { return capacity; }
        inline const char* GetData() const { return data; }

        // functions
        void Reserve(const size_t newCapacity);
        void Resize(const size_t newSize);
        void PushBack(char character);
        void Clear() noexcept;
        
    private:
        size_t UnusedCapacity()  const { return capacity - size; }
        size_t GetLastIndex()    const { return size > 0 ? size - 1 : 0; }
        size_t GetGrowthFactor() const { return capacity == 0 ? 1 : capacity * 2; }

        size_t size;
        size_t capacity;
        char* data;
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


#endif // String.hpp