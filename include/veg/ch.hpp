#pragma once

namespace vrac0x { namespace veg {


template<typename Char, Char... Args>
struct ch;


template<typename Char, Char C>
struct ch<Char, C>
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi() && *c == C) {
            ++c;
            return true;
        }
        return false;
    }
};


template<typename Char, Char C, Char... Args>
struct ch<Char, C, Args...>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return seq<ch<Char,C>, ch<Char,Args...>>::match(c);
    }

};



} } //ns
