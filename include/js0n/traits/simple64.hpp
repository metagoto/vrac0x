#pragma once

#include "simple.hpp"


namespace vrac0x { namespace js0n
{

    namespace tag
    {
        struct simple64 {};
    }


    template<typename Self>
    struct traits<Self, tag::simple64> : traits<Self, tag::simple>
    {
        typedef long long int int_type;
    };


} }
