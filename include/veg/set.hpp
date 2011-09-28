#pragma once

#include "ch.hpp"

namespace vrac0x { namespace veg {


template<typename Char, Char... Args>
struct set;


template<typename Char, Char C>
struct set<Char, C>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return ch<Char,C>::match(c);
    }
};


template<typename Char, Char C, Char... Args>
struct set<Char, C, Args...>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return ch<Char,C>::match(c) || set<Char,Args...>::match(c);
    }

};



} } //ns
