#pragma once

#include <iostream>
//#include <codecvt>


namespace vrac0x { namespace js0n
{

    // temp
    template<typename T>
    inline void print(std::ostream& o, basic_val<T> const& v)
    {
        typedef typename basic_val<T>::string string;
        typedef typename basic_val<T>::pair   pair;
        typedef typename basic_val<T>::object object;
        typedef typename basic_val<T>::array  array;
        typedef typename basic_val<T>::int_type int_type;
        typedef typename basic_val<T>::float_type float_type;

        switch (v.type())
        {
            case type_info::object:
                o << "{\n";
                for (pair const& p : get<object>(v)) {
                    o << '"' << p.first << "\": ";
                    print(o, p.second);
                    o << ",\n";
                }
                o << "}\n";
                break;
            case type_info::array:
                o << "[ ";
                for (basic_val<T> const& w : get<array>(v)) {
                    print(o, w);
                    o << ", ";
                }
                o << "]";
                break;
            case type_info::string:
                o << '"' << get<string>(v) << '"';
                break;
            case type_info::int_:
                o << get<int_type>(v);
                break;
            case type_info::double_:
                o << get<float_type>(v);
                break;
            case type_info::bool_:
                o << std::boolalpha << get<bool>(v);
                break;
            case type_info::null:
                o << "null";
                break;
            case type_info::undefined:
                o << "undefined";
                break;
            default:
                o << "*UNKNOWN*";

        }
    }


} }


template<typename T>
std::ostream& operator<<(std::ostream& o, vrac0x::js0n::basic_val<T> const& v)
{
    vrac0x::js0n::print(o, v);
    return o;
}

