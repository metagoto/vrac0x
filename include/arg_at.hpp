#pragma once

namespace vrac0x {


struct void_type {};


namespace
{
    template<std::size_t Index, std::size_t Pos, typename... T>
    struct type_at_impl;

    template<std::size_t Index, std::size_t Pos>
    struct type_at_impl<Index, Pos>
    {
        typedef void_type type;
    };

    template<std::size_t Index, typename T, typename... Tail>
    struct type_at_impl<Index, Index, T, Tail...>
    {
        typedef T type;
    };

    template<std::size_t Index, std::size_t Pos, typename T, typename... Tail>
    struct type_at_impl<Index, Pos, T, Tail...>
    {
        typedef typename type_at_impl<Index, Pos+1, Tail...>::type type;
    };


    ////

    template<std::size_t Index, std::size_t Pos, typename... T>
    struct arg_at_impl;

    template<std::size_t Index, std::size_t Pos>
    struct arg_at_impl<Index, Pos>
    {
        constexpr static void_type apply() { return void_type(); };
    };

    template<std::size_t Index, typename T, typename... Tail>
    struct arg_at_impl<Index, Index, T, Tail...>
    {
        constexpr static T apply(T&& t, Tail&&... args) { return t; }
    };

    template<std::size_t Index, std::size_t Pos, typename T, typename... Tail>
    struct arg_at_impl<Index, Pos, T, Tail...>
    {
        constexpr static auto
        apply(T&& t, Tail&&... args)
        -> typename type_at_impl<Index, Pos+1, Tail...>::type
        {
            return arg_at_impl<Index, Pos+1, Tail...>
                       ::apply(std::forward<Tail>(args)...);
        }
    };
}



template<std::size_t Index, typename... T>
struct type_at
{
    typedef typename type_at_impl<Index, 0, T...>::type type;
};


template<std::size_t Index, typename... T>
constexpr inline auto arg_at(T&&... args) -> typename type_at<Index, T...>::type
{
    return arg_at_impl<Index, 0, T...>::apply(std::forward<T>(args)...);
}


} // ns
