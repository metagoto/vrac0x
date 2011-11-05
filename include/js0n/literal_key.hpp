#pragma once


namespace vrac0x { namespace js0n
{
    inline constexpr val::k operator"" _k(val::char_type const* s, std::size_t)
    {
        return val::k(s);
    }

} }
