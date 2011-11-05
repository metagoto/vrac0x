#pragma once

#include <tuple>


namespace vrac0x
{

    inline namespace detail
    {
        template<typename R, std::size_t N>
        struct unpack
        {
            template<typename F, typename... P, typename... T>
            constexpr static R apply(F&& f, std::tuple<P...> const& p, T&&... t)
            {
                return unpack<R, N-1>
                        ::apply(std::forward<F>(f), p, std::get<N-1>(p), std::forward<T>(t)...);
            }
        };


        template<typename R>
        struct unpack<R, 0>
        {
            template<typename F, typename... P, typename... T>
            constexpr static R apply(F&& f, std::tuple<P...> const&, T&&... t)
            {
                return f(std::forward<T>(t)...);
            }
        };
    }


    template<typename F, typename... T, typename... A>
    typename std::result_of<F(T..., A...)>::type
    constexpr inline apply(F&& f, std::tuple<T...> const& tup, A&&... args)
    {
        return unpack<typename std::result_of<F(T..., A...)>::type, sizeof...(T)>
                ::apply(std::forward<F>(f), tup, std::forward<A>(args)...);
    }



}
