#pragma once


namespace vrac0x { namespace js0n
{

    struct null_type {};

    enum class type : unsigned int
    {
        undefined,
        object,
        array,
        string,
        int_,
        double_,
        bool_,
        null
    };


} }
