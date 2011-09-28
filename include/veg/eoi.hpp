#pragma once

namespace vrac0x { namespace veg {


struct eoi
{
    template<typename Context>
    static bool match(Context& c)
    {
        return c.eoi();
    }
};



} } //ns
