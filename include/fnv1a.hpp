#pragma once

// Fowler / Noll / Vo (FNV) Hash
// http://www.isthe.com/chongo/tech/comp/fnv/index.html

namespace vrac0x
{

    namespace fnv1a
    {

        inline namespace detail
        {
            constexpr uint64_t offset64= 14695981039346656037ULL;
            constexpr uint64_t prime64 = 1099511628211ULL;

            constexpr uint64_t h64(char const* c, uint64_t sink)
            {
                return *c == 0 ? sink : h64(c+1, (sink ^ *c) * prime64);
            }
        }


        template<std::size_t N>
        constexpr uint64_t h64(char const (&s)[N])
        {
            return h64(s, offset64);
        }

    }

}
