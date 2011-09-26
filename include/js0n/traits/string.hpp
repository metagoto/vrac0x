#pragma once

#include <string>


namespace vrac0x { namespace js0n
{

    template<typename Self>
    struct traits<Self, tag::string>
    {
        typedef std::string string_type;

        typedef typename string_type::value_type char_type;
    };


    template<typename Self>
    struct traits<Self, tag::u8string> // same as above btw
    {
        typedef std::string string_type;

        typedef typename string_type::value_type char_type;
    };


    template<typename Self>
    struct traits<Self, tag::u16string>
    {
        typedef std::u16string string_type;

        typedef typename string_type::value_type char_type;
    };


    template<typename Self>
    struct traits<Self, tag::u32string>
    {
        typedef std::u32string string_type;

        typedef typename string_type::value_type char_type;
    };


} }
