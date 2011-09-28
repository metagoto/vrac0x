#pragma once

namespace vrac0x { namespace veg {


template<typename Char>
struct any_ch
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi()) {
            ++c;
            return true;
        }
        return false;
    }
};

// TODO implement with not<>
template<typename Char, Char C>
struct any_ch_but
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi() && *c != C) {
            ++c;
            return true;
        }
        return false;
    }
};



} } //ns
