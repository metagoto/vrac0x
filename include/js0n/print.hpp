#pragma once

#include <iostream>
//#include <codecvt>


namespace vrac0x { namespace js0n
{

    // temp
    template<typename T>
    inline void print(basic_val<T> const& v)
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
                std::cout << "{\n";
                for (pair const& p : get<object>(v)) {
                    std::cout << '"' << p.first << "\": ";
                    print(p.second);
                    std::cout << ",\n";
                }
                std::cout << "}\n";
                break;
            case type_info::array:
                std::cout << "[ ";
                for (basic_val<T> const& w : get<array>(v)) {
                    print(w);
                    std::cout << ", ";
                }
                std::cout << "]";
                break;
            case type_info::string:
                std::cout << '"' << get<string>(v) << '"';
                break;
            case type_info::int_:
                std::cout << get<int_type>(v);
                break;
            case type_info::double_:
                std::cout << get<float_type>(v);
                break;
            case type_info::bool_:
                std::cout << std::boolalpha << get<bool>(v); //(bool)v;
                break;
            case type_info::null:
                std::cout << "null";
                break;
            case type_info::undefined:
                std::cout << "undefined";
                break;
            default:
                std::cout << "*UNKNOWN*";

        }
    }


} }


template<typename T>
std::ostream& operator<<(std::ostream& o, vrac0x::js0n::basic_val<T> const& v)
{
    vrac0x::js0n::print(v);
    return o;
}

