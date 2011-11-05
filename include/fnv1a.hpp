#pragma once

#include <cstdint>

// Fowler / Noll / Vo (FNV) Hash
// http://www.isthe.com/chongo/tech/comp/fnv/index.html

namespace vrac0x { namespace fnv1a
{

    namespace detail
    {
        constexpr uint64_t offset64= 14695981039346656037ULL;
        constexpr uint64_t prime64 = 1099511628211ULL;

        template<typename T>
        inline constexpr uint64_t h64(T const* c, uint64_t sink)
        {
            return *c == 0 ? sink : h64(c+1, (sink ^ *c) * prime64);
        }


        template<uint64_t Sink, char... C>
        struct s64;

        template<uint64_t Sink, char C>
        struct s64<Sink, C>
        {
            static constexpr uint64_t value = (Sink ^ C) * prime64;
        };

        template<uint64_t Sink, char C, char... T>
        struct s64<Sink, C, T...>
        {
            static constexpr uint64_t value = s64<(Sink ^ C) * prime64, T...>::value;
        };

    }


    template<typename T, std::size_t N>
    inline constexpr uint64_t h64(T const (&s)[N])
    {
        return detail::h64(s, detail::offset64);
    }


    template<typename T>
    inline constexpr uint64_t h64(T const* s, std::size_t)
    {
        return detail::h64(s, detail::offset64);
    }


    template<char... C>
    inline constexpr uint64_t h64()
    {
        return detail::s64<detail::offset64, C...>::value;
    }



    namespace literals
    {
        inline constexpr uint64_t operator"" _h64(char const* s, std::size_t n)
        {
            return vrac0x::fnv1a::h64(s, n);
        }

        template<char... C>
        inline constexpr uint64_t operator"" _h64()
        {
            return vrac0x::fnv1a::h64<C...>();
        }
    }



} }
