#pragma once

#include <type_traits>

namespace mystd
{
    template <class T, size_t Size>
    class array
    {
    public:
        static_assert(is_object_v<T>, "T must be object because of [container.requirements]");

        T Array[Size];
    private:
    };
} // namespace mystd
