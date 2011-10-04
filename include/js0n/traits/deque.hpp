#pragma once

#include <deque>
#include "simple.hpp"


namespace vrac0x { namespace js0n
{

    namespace tag
    {
        struct deque {};
    }


    template<typename Self>
    struct traits<Self, tag::deque> : traits<Self, tag::simple>
    {
        typedef traits<Self, tag::simple> base;

        typedef std::deque<Self>                     array_type;
        typedef std::deque<typename base::pair_type> object_type;
    };


} }
