#pragma once

namespace mystd
{
    template <size_t Size>
    class fixed_string
    {
    public:
        
        inline       T& front() noexcept       { return Elements[0]; }
        inline const T& front() const noexcept { return Elements[0]; }
        inline       T& back() noexcept        { return Elements[Size]; }
        inline const T& back() const noexcept  { return Elements[Size]; }
        
        inline       T* data() noexcept       { return Elements; }
        inline const T* data() const noexcept { return Elements; }

    private:
        char Elements[Size + 1];
    };
} // namespace mystd
