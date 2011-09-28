#pragma once

namespace vrac0x { namespace veg {


template<typename T>
struct opt
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi()) {
            T::match(c);
        }
        return true;
    }
};



} } //ns
