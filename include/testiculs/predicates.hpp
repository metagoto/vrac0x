#pragma once

#include <utility>
#include <type_traits>
#include <cstring>


namespace vrac0x { namespace testiculs {


    namespace predicate
    {

        // this is tricky
        template<typename... T>
        struct holder
        {
            template<bool F(T...)>
            struct not_
            {
                template<typename... U>
                inline bool operator()(U&&... a) const
                {
                    return !F(std::forward<U>(a)...);
                }
            };
        };


        inline bool test(bool a)
        {
            return a;
        }


        template<typename T, typename U>
        inline bool eq(T const& a, U const& b)
        {
            return a == b;
        }


        inline bool str_eq(char const* a, char const* b)
        {
            if (a == nullptr)
                return b == nullptr;
            if (b == nullptr)
                return false;
            return std::strcmp(a, b) == 0;
        }


    }

} }
