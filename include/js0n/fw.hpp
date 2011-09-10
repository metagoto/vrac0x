#pragma once

#include <string>
#include <vector>


namespace vrac0x { namespace js0n
{

    struct k;

    struct val;


    typedef std::string string;

    typedef std::pair<string, val> pair;

    typedef std::vector<pair> object;

    typedef std::vector<val> array;


    enum class type : unsigned int;

} }
