#include <iostream>

#include "include/fnv1a.hpp"


// runtime hash
uint64_t fnv1a_64(char const* s)
{
    uint64_t const p = 1099511628211ULL;
    uint64_t h = 14695981039346656037ULL;
    for ( ; *s; ++s)
        h = (h ^ *s) * p;
    return h;
}



template<uint64_t H>
struct check
{
    static const uint64_t value = H;
};


namespace dum
{
    using namespace vrac0x::fnv1a;

    template<uint64_t T>
    struct a
    {
        static const bool value = false;
    };


    template<>
    struct a<h64("dispatch")>
    {
        static const bool value = true;
    };

}



#define TEST1(str) std::cout << str << " " << fnv1a_64(str) << " " \
    << (fnv1a_64(str) == check<h64(str)>::value) << std::endl;

#define TEST2(t, v) std::cout << (dum::a<t>::value == v) << std::endl;


int main()
{

    using vrac0x::fnv1a::h64;

    TEST1("hello world")
    TEST1("salut")
    TEST1("saluv")
    TEST1("")


    TEST2(0,              false)
    TEST2(h64("blah"),    false)
    TEST2(h64("dispatch"),true)

}
