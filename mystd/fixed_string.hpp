#pragma once

#include "array.hpp"

#include <iostream>

namespace mystd
{
    template <size_t Capacity>
    class fixed_string
    {
    public:
        using data_type = mystd::array<char, Capacity + 1>;
        using data_iterator_type = mystd::array<char, Capacity>;
        using iterator = typename data_iterator_type::iterator;
        using const_iterator = typename data_iterator_type::const_iterator;

        fixed_string() = default;
        ~fixed_string() = default;

        fixed_string(const char* c_str) {
            _size = strlen(c_str);
            assert(_size <= Capacity && "c_str Size can't be larger than Capacity");
            memcpy(data(), c_str, _size + 1); // with NULL symbol
        }
        fixed_string(const char (&array)[Capacity + 1]) noexcept {
            _size = Capacity;
            memcpy(data(), array, _size + 1); // with NULL symbol
        }
        fixed_string(const fixed_string& other) noexcept {
            _size = other._size;
            memcpy(data(), other._data, _size + 1); // with NULL symbol
        }
        
        fixed_string& operator=(const char* c_str) {
            if (data() == c_str) return *this;

            _size = strlen(c_str);
            assert(_size <= Capacity && "c_str Size can't be larger than Capacity");
            memcpy(data(), c_str, _size + 1); // with NULL symbol
            return *this;
        }
        fixed_string& operator=(const char (&array)[Capacity + 1]) noexcept {
            if (data() == array) return *this;

            _size = Capacity;
            memcpy(data(), array, _size + 1); // with NULL symbol
            return *this;
        }
        fixed_string& operator=(const fixed_string& other) {
            if (data() == other.data()) return *this;

            _size = other._size;
            memcpy(_data.data(), other._data, _size + 1); // with NULL symbol
            return *this;
        }
        
        fixed_string(fixed_string&& other) noexcept = delete;
        fixed_string& operator=(fixed_string&& other) noexcept = delete;

        constexpr iterator       begin() noexcept        { return _data.begin(); }
        constexpr const_iterator begin() const noexcept  { return _data.begin(); }
        constexpr iterator       end() noexcept          { return _data.begin() + _size; }
        constexpr const_iterator end() const noexcept    { return _data.begin() + _size; }
        constexpr const_iterator cbegin() const noexcept { return _data.cbegin(); }
        constexpr const_iterator cend() const noexcept   { return _data.cbegin() + _size; }

        inline char&       operator[](const size_t pos) noexcept { return _data[pos]; }
        inline const char& operator[](const size_t pos) const noexcept { return _data[pos]; }
        inline char&       at(const size_t pos) noexcept{ return _data.at(pos); }
        inline const char& at(const size_t pos) const noexcept { return _data.at(pos); }

        inline       char& front() noexcept       { return _data[0]; }
        inline const char& front() const noexcept { return _data[0]; }
        inline       char& back() noexcept        { return _data[Capacity]; }
        inline const char& back() const noexcept  { return _data[Capacity]; }

        constexpr size_t size() const noexcept { return _size; }
        void setSize(const size_t size) const {
            assert(_size <= Capacity && "size can't be larger than Capacity");
            _size = size;
        }
        
        inline       char*  data() noexcept       { return _data.data(); }
        inline const char*  data() const noexcept { return _data.data(); }
        
    private:
        size_t _size;
        data_type _data;
    };
    
    template <size_t Capacity>
    constexpr bool operator==(const fixed_string<Capacity>& lhs, const fixed_string<Capacity>& rhs)
        { return lhs.data() == rhs.data(); }
    template <size_t Capacity>
    constexpr bool operator==(const fixed_string<Capacity>& lhs, const char (&rhs)[Capacity + 1])
        { return lhs.data() == rhs; }
    template <size_t Capacity>
    constexpr bool operator==(const fixed_string<Capacity>& lhs, const char* rhs)
        { return lhs.data() == rhs; }
    
    template <size_t Capacity>
    constexpr bool operator!=(const fixed_string<Capacity>& lhs, const fixed_string<Capacity>& rhs)
        { return lhs.data() != rhs.data(); }
    template <size_t Capacity>
    constexpr bool operator!=(const fixed_string<Capacity>& lhs, const char (&rhs)[Capacity + 1])
        { return lhs.data() != rhs; }
    template <size_t Capacity>
    constexpr bool operator!=(const fixed_string<Capacity>& lhs, const char* rhs)
        { return lhs.data() != rhs; }

    template <size_t Capacity1, size_t Capacity2>
    constexpr fixed_string<Capacity1 + Capacity2> operator+(const fixed_string<Capacity1>& lhs, const fixed_string<Capacity2>& rhs)
    {
        fixed_string<Capacity1 + Capacity2> result;
        result.setSize(Capacity1 + Capacity2);
        memset(result.data(), lhs.data(), lhs.size());
        memset(result.data() + lhs.size(), rhs.data(), rhs.size() + 1);
        return result;
    }
    template <size_t Capacity1, size_t Capacity2>
    constexpr fixed_string<Capacity1 + Capacity2> operator+(const fixed_string<Capacity1>& lhs, const char (&rhs)[Capacity2 + 1])
    {
        fixed_string<Capacity1 + Capacity2> result;
        result.setSize(Capacity1 + Capacity2);
        memset(result.data(), lhs.data(), lhs.size());
        memset(result.data() + lhs.size(), rhs.data(), rhs.size() + 1);
        return result;
    }
    
    template <size_t Capacity>
    std::istream& operator>>(std::istream& is, fixed_string<Capacity>& str) {
        char temp;
        size_t counter = 1;
        is.get(temp);
    
        while (temp != '\n' && counter <= Capacity)
        {
            str.push_back(temp);
            is.get(temp);
            counter++;
        }
        str.setSize(counter);
        str[counter] = 0;
    
        return is;
    }
    template <size_t Capacity>
    std::ostream& operator<<(std::ostream& os, fixed_string<Capacity>& str) {
        for (size_t i = 0; i < str.size(); i++)
            os << str[i];
        return os;
    }
    
} // namespace mystd
