#pragma once

#include <iostream>
#include <tuple>


namespace vrac0x
{

    template<std::size_t I = 0, typename... T>
    inline typename std::enable_if<I == sizeof...(T), void>::type
    print_tuple(std::ostream& os, std::tuple<T...> const& t)
    { }


    template<std::size_t I = 0, typename... T>
    inline typename std::enable_if<I < sizeof...(T), void>::type
    print_tuple(std::ostream& os, std::tuple<T...> const& t)
    {
        os << std::get<I>(t);

        if (I < sizeof...(T)-1)
            os << ", ";

        print_tuple<I+1, T...>(os, t);
    }



}


template<typename... T>
std::ostream& operator<<(std::ostream& os, std::tuple<T...> const& t)
{
    vrac0x::print_tuple(os, t);
    return os;
}
