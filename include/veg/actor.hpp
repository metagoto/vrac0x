#pragma once

namespace vrac0x { namespace veg {


template<typename T, typename A>
struct actor
{
    template<typename Context>
    static bool match(Context& c)
    {
        auto s = c.pos();
        if (T::match(c)) {
            A()(s, c.pos());
            return true;
        }
        return false;
    }
};


} } //ns
