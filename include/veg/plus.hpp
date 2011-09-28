#pragma once

namespace vrac0x { namespace veg {


template<typename T>
struct plus
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!T::match(c)) return false;
        return star<T>::match(c);
    }
};



} } //ns
