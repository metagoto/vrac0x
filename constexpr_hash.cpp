
#include "include/fnv1a.hpp"
#include "include/testiculs.hpp"


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


int main()
{

    using vrac0x::fnv1a::h64;

    CHECK(fnv1a_64("") == h64(""));
    CHECK(fnv1a_64("hello world") == h64("hello world"));

    constexpr auto a = h64("abcd");
    CHECK_EQ(fnv1a_64("abcd"), a);
    CHECK(fnv1a_64("abcd") == a);

    constexpr auto b = check<h64("xyz")>::value;
    CHECK_EQ(fnv1a_64("xyz"), b);

    CHECK_EQ(fnv1a_64("blah"), static_cast<uint64_t>(check<h64("blah")>::value));

    CHECK_NEQ(h64("salut"), h64("saluv"));

    PRINT(fnv1a_64("hello world"));
    PRINT(h64("hello world"));

    PRINT(fnv1a_64(""));
    PRINT(h64(""));

    PRINT(fnv1a_64(" "));
    PRINT(h64(" "));

    STATIC_ASSERT(check<h64("hello world")>::value);
    STATIC_ASSERT(dum::a<h64("dispatch")>::value);
    STATIC_ASSERT_NOT(dum::a<h64("blah")>::value);
    STATIC_ASSERT_NOT(dum::a<h64("")>::value);

}
