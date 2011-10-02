#pragma once

#include "simple64.hpp"


namespace vrac0x { namespace js0n
{

    namespace tag
    {
        struct large {};
    }


    template<typename Self>
    struct traits<Self, tag::large> : traits<Self, tag::simple64>
    {
        typedef long double float_type;
    };


} }
