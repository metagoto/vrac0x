#include <iostream>
#include <tuple>
#include <cstring>

#include "unpack.hpp"
#include "tupility.hpp"

namespace vrac0x { namespace testiculs
{


    inline namespace predicate
    {

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
            return strcmp(a, b) == 0;
        }

    }



    template<typename... E, typename F, typename... T>
    inline void test(F const& f, std::tuple<T...> const& t
                    ,std::tuple<E...> const& e
                    ,char const* test, char const* file, std::size_t line)
    {
        if (vrac0x::unpack_apply(f, t))
            std::cout << " PASS " << test << " " << e << std::endl;

        else
            std::cout << "-FAIL " << file << ":" << line << ": "
                                  << test << " " << e << std::endl;

    }

} }


#define _T_INFO(t) #t, __FILE__, __LINE__
#define _T_INFO2(t,a,b) std::make_tuple(a, b), std::make_tuple(#a, #b), _T_INFO(t)

#define CHECK_EQ(a,b) \
        vrac0x::testiculs::test(&vrac0x::testiculs::predicate::eq<decltype(a),decltype(b)> \
                               ,_T_INFO2(CHECK_EQ, a, b));

#define CHECK_STREQ(a,b) \
        vrac0x::testiculs::test(&vrac0x::testiculs::predicate::str_eq \
                               ,_T_INFO2(CHECK_STREQ, a, b));

