#pragma once

namespace vrac0x { namespace veg {


template<typename T>
struct store
{
    template<typename Context>
    static bool match(Context& c)
    {
        c.tree().template create_node<T>(c.pos());
        if (T::match(c)) {
            c.tree().finalize_node(c.pos());
            return true;
        }
        c.tree().forget_node();
        return false;
    }
};



} } //ns
