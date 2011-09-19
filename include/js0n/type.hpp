#pragma once


namespace vrac0x { namespace js0n
{

    struct null_type {};
    struct empty_object_type {};
    struct empty_array_type {};

    enum class type_info : unsigned int
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


    // predefined constants
    null_type const null = {};
    empty_array_type const empty_array = {};
    empty_object_type const empty_object = {};


} }
