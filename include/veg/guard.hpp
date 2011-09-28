#pragma once

namespace vrac0x { namespace veg {

template<typename Context>
struct guard
{

    guard(Context& c)
        : context(c)
        , it(c.pos())
        , dismissed(false)
    {

    }

    ~guard()
    {
        if (!dismissed)
            context.pos(it);
    }

    bool dismiss()
    {
        return dismissed = true; // yes
    }

    Context& context;
    typename Context::iterator_type it;
    bool dismissed;

};


} } //ns
