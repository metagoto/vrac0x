#pragma once

#include "simple.hpp"


namespace vrac0x { namespace js0n
{

    namespace tag
    {
        struct compact {};
    }


    template<typename Self>
    struct traits<Self, tag::compact> : traits<Self, tag::simple>
    {
        typedef short int int_type;
        typedef float     float_type;
    };


} }
