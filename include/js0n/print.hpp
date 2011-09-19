#pragma once


namespace vrac0x { namespace js0n
{

    // temp
    inline void print(val const& j)
    {

        switch (j.type())
        {
            case type_info::object:
                std::cout << "{\n";
                for (pair const& p : get<object>(j)) {
                    std::cout << p.first << ": ";
                    print(p.second);
                    std::cout << ",\n";
                }
                std::cout << "}\n";
                break;
            case type_info::array:
                std::cout << "[ ";
                for (val const& v : get<array>(j)) {
                    print(v);
                    std::cout << ", ";
                }
                std::cout << "]";
                break;
            case type_info::string:
                std::cout << get<string>(j);
                break;
            case type_info::int_:
                std::cout << (int)j;
                break;
            case type_info::double_:
                std::cout << (double)j;
                break;
            case type_info::bool_:
                std::cout << ((bool)j ? "*true*" : "*false*");
                break;
            case type_info::null:
                std::cout << "*null*";
                break;
            case type_info::undefined:
                std::cout << "*undefined*";
                break;
            default:
                std::cout << "*UNKNOWN*";

        }
    }


} }


std::ostream& operator<<(std::ostream& o, vrac0x::js0n::val const& v)
{
    print(v);
    return o;
}
