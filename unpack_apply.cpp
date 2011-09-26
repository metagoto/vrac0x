
#include <iostream>

#include "include/apply.hpp"


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
    using vrac0x::apply;

    apply(f, std::make_tuple('c'));

    apply(functor(), std::make_tuple(std::string{"hello"}, 42));

    apply(v, std::tuple<>());

    apply([](int a, float b, char c){
        std::cout << a << b << c << std::endl;
    }, std::make_tuple(2, 3.14f), 'z');

    apply(functor(), tup());

    std::size_t i{3};
    std::tuple<std::string, std::size_t> t{"lut", i};
    apply(functor(), t);


}
