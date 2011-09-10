#pragma once


namespace vrac0x { namespace js0n
{

    // temp
    inline void print(vrac0x::js0n::val const& j)
    {

        using namespace vrac0x::js0n;

        switch (j.type_)
        {
            case type::object:
                std::cout << "{\n";
                for (pair const& p : j.o_) {
                    std::cout << p.first << ": ";
                    print(p.second);
                }
                std::cout << "}" << std::endl;
                break;
            case type::array:
                std::cout << "[\n";
                for (val const& v : j.a_) {
                    print(v);
                }
                std::cout << "]" << std::endl;
                break;
            case type::string:
                std::cout << j.s_ << std::endl;
                break;
            case type::int_:
                std::cout << j.i_ << std::endl;
                break;
            case type::double_:
                std::cout << j.d_ << std::endl;
                break;
            case type::bool_:
                std::cout << (j.b_ ? "true" : "false") << std::endl;
                break;
            case type::null:
                std::cout << "*null*" << std::endl;
                break;
            case type::undefined:
                std::cout << "*undefined*" << std::endl;
                break;
            default:
                std::cout << "*UNKNOWN*" << std::endl;

        }

    }


} }
