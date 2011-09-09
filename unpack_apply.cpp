
#include <iostream>

#include "include/unpack.hpp"


int f(char c)
{
    std::cout << c << std::endl;
    return 0;
}


struct functor
{
    void operator()(std::string s, std::size_t n)
    {
        std::cout << s << " " << n << std::endl;
    }
};


void v()
{
    std::cout << "v()" << std::endl;
}


std::tuple<std::string, int> tup()
{
    return std::make_tuple(std::string{"hi"}, 1);
}



int main()
{
    using namespace vrac0x;

    unpack_apply(f, std::make_tuple('c'));

    unpack_apply(functor(), std::make_tuple(std::string{"hello"}, 42));

    unpack_apply(v, std::tuple<>());

    unpack_apply([](int a, float b, char c){
        std::cout << a << b << c << std::endl;
    }, std::make_tuple(2, 3.14f), 'z');

    unpack_apply(functor(), tup());

    std::size_t i{3};
    std::tuple<std::string, std::size_t> t{"lut", i};
    unpack_apply(functor(), t);


}
