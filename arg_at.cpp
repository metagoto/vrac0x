#include <iostream>
#include <type_traits>
#include <ext/typelist.h> // __gnu_cxx

#include "include/arg_at.hpp"


namespace fixture
{
    typedef __gnu_cxx::typelist::append<
        typename __gnu_cxx::typelist::create6<
            int&&
           ,float&&
           ,char&&
           ,char const (&)[3]
           ,std::string const&
           ,std::string&
        >::type, typename __gnu_cxx::typelist::create3<
            int&
           ,int*&
           ,int*&&
        >::type
    >::type type_list ;

    template<std::size_t Index>
    struct type_at
    {
        typedef typename __gnu_cxx::typelist::at_index<type_list, Index>::type type;
    };


#define TEST(I) {\
    std::string const cs{"cstr"}; \
    std::string s{"str"}; \
    int i{42}; \
    int* pi = &i; \
    std::cout << \
    \
    test<I>::f(2, 3.14f, 'c', "hi", cs, s, i, pi, &i) \
    \
    << std::endl; }

}


template<std::size_t Index>
struct test
{

    template<typename... T>
    static auto f(T&&... args) -> typename vrac0x::type_at<Index, T...>::type
    {

        using vrac0x::type_at;
        using vrac0x::arg_at;

        static_assert(
            std::is_same<
                decltype(std::declval<typename type_at<Index, T...>::type>()),
                typename fixture::type_at<Index>::type
            >::value, "FAIL");

        return arg_at<Index>(std::forward<T>(args)...);
    }
};



int main()
{

    TEST(0)
    TEST(1)
    TEST(2)
    TEST(3)
    TEST(4)
    TEST(5)
    TEST(6)
    TEST(7)
    TEST(8)
    //TEST(9)
}
