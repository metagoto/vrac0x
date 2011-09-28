#pragma once

#include "alter.hpp"

namespace vrac0x { namespace veg {


template<typename Char, Char... Args>
struct range;


template<typename Char, Char L, Char R>
struct range<Char, L, R>
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi() && *c >= L && *c <= R) {
            ++c;
            return true;
        }
        return false;
    }
};


template<typename Char, Char L, Char R, Char... Args>
struct range<Char, L, R, Args...>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return alter<range<Char,L,R>, range<Char,Args...>>::match(c);
    }
};


} } //ns
