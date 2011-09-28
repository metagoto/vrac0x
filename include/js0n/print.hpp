#pragma once

//#include <codecvt>


namespace vrac0x { namespace js0n
{

    // temp
    template<typename S, typename C>
    inline void print(basic_val<S,C> const& v)
    {
        typedef typename basic_val<S,C>::string string;
        typedef typename basic_val<S,C>::pair   pair;
        typedef typename basic_val<S,C>::object object;
        typedef typename basic_val<S,C>::array  array;

        switch (v.type())
        {
            case type_info::object:
                std::cout << "{\n";
                for (pair const& p : get<object>(v)) {
                    std::cout << p.first << ": ";
                    print(p.second);
                    std::cout << ",\n";
                }
                std::cout << "}\n";
                break;
            case type_info::array:
                std::cout << "[ ";
                for (basic_val<S,C> const& w : get<array>(v)) {
                    print(w);
                    std::cout << ", ";
                }
                std::cout << "]";
                break;
            case type_info::string:
                std::cout << '"' << (char const*)v << '"';
                break;
            case type_info::int_:
                std::cout << (int)v;
                break;
            case type_info::double_:
                std::cout << (double)v;
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


template<typename S, typename C>
std::ostream& operator<<(std::ostream& o, vrac0x::js0n::basic_val<S,C> const& v)
{
    vrac0x::js0n::print(v);
    return o;
}

