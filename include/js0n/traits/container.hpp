#pragma once

#include <vector>
#include <deque>


namespace vrac0x { namespace js0n
{

    template<typename Self>
    struct traits<Self, tag::vector>
    {
        typedef typename Self::string string_type;

        typedef std::pair<string_type, Self> pair_type;

        typedef std::vector<Self> array_type;

        typedef std::vector<pair_type> object_type;

    };


    template<typename Self>
    struct traits<Self, tag::deque>
    {
        typedef typename Self::string string_type;

        typedef std::pair<string_type, Self> pair_type;

        typedef std::deque<Self> array_type;

        typedef std::deque<pair_type> object_type;

    };


} }
