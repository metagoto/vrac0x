#pragma once

#include "guard.hpp"


namespace vrac0x { namespace veg {


template<typename T, unsigned int N>
struct repeat
{
    template<typename Context>
    static bool match(Context& c)
    {
        //auto i = c.pos();
        guard<Context> g(c);
        for (unsigned int n = 0; n < N; ++n) {
            if (!T::match(c)) {
                //c.pos(i);
                return false;
                //return g.dismiss();
            }
        }
        //return true;
        return g.dismiss();
    }
};



} } //ns
