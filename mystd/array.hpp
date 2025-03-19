#pragma once

#include <type_traits>
#include <cassert>

namespace mystd
{
    template <typename T, size_t Size>
    class array_const_iterator;
    template <typename T, size_t Size>
    class array_iterator;

    template <typename T, size_t Size>
    class array
    {
    public:
        static_assert(std::is_object_v<T>, "T must be object because of [container.requirements]");

        using iterator = array_iterator<T, Size>;
        using const_iterator = array_const_iterator<T, Size>;

        inline constexpr T size() const noexcept { return Size; }

        inline iterator       begin() noexcept       { return iterator(Elements, 0); }
        inline const_iterator begin() const noexcept { return const_iterator(Elements, 0); }
        inline iterator       end() noexcept         { return iterator(Elements, Size); }
        inline const_iterator end() const noexcept   { return const_iterator(Elements, Size); }

        inline T& at(const size_t pos) noexcept {
            assert(pos < Size && "Pos out of array range");
            return Elements[pos];
        }
        inline const T& at(const size_t pos) const noexcept {
            assert(pos < Size && "Pos out of array range");
            return Elements[pos];
        }

        inline T& operator[](const size_t pos) noexcept {
            assert(pos < Size && "Pos out of array range");
            return Elements[pos];
        }
        inline const T& operator[](const size_t pos) const noexcept {
            assert(pos < Size && "Pos out of array range");
            return Elements[pos];
        }

        inline       T& front() noexcept       { return Elements[0]; }
        inline const T& front() const noexcept { return Elements[0]; }
        inline       T& back() noexcept        { return Elements[Size - 1]; }
        inline const T& back() const noexcept  { return Elements[Size - 1]; }

        inline       T* data() noexcept       { return Elements; }
        inline const T* data() const noexcept { return Elements; }

        T Elements[Size];
    };

    template <typename T, size_t Size>
    class array_const_iterator
    {
    public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::random_access_iterator_tag;
        
        inline array_const_iterator() noexcept { }
        inline explicit array_const_iterator(pointer ptr, size_t offset) noexcept
            : ptr(ptr), offset(offset) { }

        inline reference operator*() const noexcept // get reference of result
            { return *operator->(); }
        inline pointer operator->() const noexcept { // get pointer of result
            assert(ptr && "Pointer can't be nullptr");
            assert(offset < Size && "Offset out of array range");
            return ptr + offset;
        }

        inline array_const_iterator& operator++() noexcept { // prefix
            assert(ptr && "Pointer can't be nullptr");
            assert(offset < Size && "Offset out of array range");
            ++offset;
            return *this;
        }
        inline array_const_iterator operator++(int) noexcept { // postfix
            array_const_iterator temp = *this;
            ++*this;
            return temp;
        }
        inline array_const_iterator& operator--() noexcept { // prefix
            assert(ptr && "Pointer can't be nullptr");
            assert(offset != 0 && "Offset out of array range");
            --offset;
            return *this;
        }
        inline array_const_iterator operator--(int) noexcept { // postfix
            array_const_iterator temp = *this;
            --*this;
            return temp;
        }

        inline bool operator==(const array_const_iterator& other) const noexcept {
            assert(ptr == other.ptr && "Array iterators incompatible");
            return offset == other.offset;
        }
        inline bool operator!=(const array_const_iterator& other) const noexcept { return !(*this == other); }
        
        // in std::array not using this realization, offset usage
        inline bool operator<(const array_const_iterator& other) const noexcept {
            assert(ptr && "ptr can't be nullptr");
            assert(other.ptr && "other.ptr can't be nullptr");
            return ptr + offset < other.ptr + other.offset;
        }

        inline bool operator>(const array_const_iterator& other) const noexcept { return other < *this; }
        inline bool operator<=(const array_const_iterator& other) const noexcept { return !(other < *this); }
        inline bool operator>=(const array_const_iterator& other) const noexcept { return !(*this < other); }

    private:
        pointer ptr;
        size_t offset;
    };

    template <typename T, size_t Size>
    class array_iterator : public array_const_iterator<T, Size>
    {
    public:
        using base = array_const_iterator<T, Size>;

        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::random_access_iterator_tag;
        
        inline array_iterator() noexcept { }
        inline explicit array_iterator(pointer ptr, size_t offset) noexcept
            : base(ptr, offset) { }
        
        inline reference operator*() const noexcept { return const_cast<reference>(base::operator*()); }
        inline pointer operator->() const noexcept  { return const_cast<pointer>(base::operator->()); }

        inline array_iterator& operator++() noexcept { // prefix
            base::operator++();
            return *this;
        }
        inline array_iterator operator++(int) noexcept { // postfix
            array_iterator temp = *this;
            base::operator++();
            return temp;
        }
        inline array_iterator& operator--() noexcept { // prefix
            base::operator--();
            return *this;
        }
        inline array_iterator operator--(int) noexcept { // postfix
            array_iterator temp = *this;
            base::operator--();
            return temp;
        }
    };

} // namespace mystd
