#pragma once

#include "guard.hpp"

namespace vrac0x { namespace veg {


template<typename T>
struct until_past
{

    template<typename Context>
    static bool match(Context& c)
    {
        //auto i = c.pos();
        guard<Context> g(c);
        while (true) {
            if (T::match(c)) {
                return g.dismiss();
            }
            ++c;
            if (c.eoi()) {
                //c.pos(i);
                return false;
            }
        }
        return false;
    }

};



} } //ns
