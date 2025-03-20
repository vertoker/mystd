#pragma once

#include "array.hpp"

namespace mystd
{
    template <size_t Capacity>
    class fixed_string
    {
    public:
        fixed_string() = default;
        fixed_string(const char* c_str) {
            auto strSize = strlen(c_str);
            assert(strSize <= Capacity && "c_str Size can't be larger than Capacity");
            std::copy(, _data.begin());
        }
        
        fixed_string(const fixed_string& other);
        fixed_string& operator=(const fixed_string& other);
        
        fixed_string(fixed_string&& other) noexcept = delete;
        fixed_string& operator=(fixed_string&& other) noexcept = delete;
        ~fixed_string() = default;

        constexpr iterator               begin() noexcept { return _data.begin(); }
        constexpr const_iterator         begin() const noexcept { return _data.begin(); }
        constexpr iterator               end() noexcept { return _data.end() - 1; }
        constexpr const_iterator         end() const noexcept { return _data.end() - 1; }
        constexpr const_iterator         cbegin() const noexcept { return _data.cbegin(); }
        constexpr const_iterator         cend() const noexcept { return _data.cend() - 1; }

	    inline char& operator[](size_t index) const { return _data[index]; }

        inline char&       operator[](size_t pos) { return _data[pos]; }
        inline const char& operator[](size_t pos) const { return _data[pos]; }
        inline char&       at(size_t pos) { return _data.at(pos); }
        inline const char& at(size_t pos) const { return _data.at(pos); }

        inline       T& front() noexcept       { return _data[0]; }
        inline const T& front() const noexcept { return _data[0]; }
        inline       T& back() noexcept        { return _data[Capacity]; }
        inline const T& back() const noexcept  { return _data[Capacity]; }
        inline       T* data() noexcept       { return _data; }
        inline const T* data() const noexcept { return _data; }
        
    private:
        size_t _size;
        mystd::array<char, Capacity + 1> _data;
    };
    
    template <size_t Capacity>
    constexpr bool operator==(const fixed_string<Capacity>& lhs, const fixed_string<Capacity>& rhs)
    {
        return lhs.data() == rhs.data();
    }
} // namespace mystd
