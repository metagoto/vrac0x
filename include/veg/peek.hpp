#pragma once

#include "guard.hpp"

namespace vrac0x { namespace veg {


template<typename T>
struct peek
{
    template<typename Context>
    static bool match(Context& c)
    {
        //auto i = c.pos();
        guard<Context> g(c);
        if (T::match(c)) {
            //c.pos(i);
            return true;
        }
        return false;
    }
};



} } //ns
