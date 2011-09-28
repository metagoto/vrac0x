#pragma once

namespace vrac0x { namespace veg {


template<typename... Args>
struct alter;

template<typename T>
struct alter<T>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return T::match(c);
    }
};

template<typename T, typename ...Args>
struct alter<T, Args...>
{
    typedef alter<Args...> rest;

    template<typename Context>
    static bool match(Context& c)
    {
        return T::match(c) || rest::match(c);
    }
};



} } //ns
