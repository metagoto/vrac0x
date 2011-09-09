#pragma once

namespace vrac0x
{

    inline namespace detail
    {
        template<std::size_t Index, typename... T>
        struct type_at_impl;

        template<typename T, typename... Tail>
        struct type_at_impl<0, T, Tail...>
        {
            typedef T type;
        };

        template<std::size_t Index, typename T, typename... Tail>
        struct type_at_impl<Index, T, Tail...>
        {
            typedef typename type_at_impl<Index-1, Tail...>::type type;
        };

        ////

        template<std::size_t Index, typename... T>
        struct arg_at_impl;

        template<typename T, typename... Tail>
        struct arg_at_impl<0, T, Tail...>
        {
            constexpr static T apply(T&& t, Tail&&... args) { return t; }
        };

        template<std::size_t Index, typename T, typename... Tail>
        struct arg_at_impl<Index, T, Tail...>
        {
            constexpr static auto
            apply(T&& t, Tail&&... args)
            -> typename type_at_impl<Index-1, Tail...>::type
            {
                return arg_at_impl<Index-1, Tail...>
                        ::apply(std::forward<Tail>(args)...);
            }
        };
    }



    template<std::size_t Index, typename... T>
    struct type_at
    {
        typedef typename type_at_impl<Index, T...>::type type;
    };


    template<std::size_t Index, typename... T>
    constexpr inline auto arg_at(T&&... args) -> typename type_at<Index, T...>::type
    {
        return arg_at_impl<Index, T...>::apply(std::forward<T>(args)...);
    }



}
