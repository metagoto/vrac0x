#pragma once

#include <iostream>

#include "../apply.hpp"
#include "../tupility.hpp"


namespace vrac0x { namespace testiculs
{

    inline namespace detail
    {
        typedef std::tuple<char const*, char const*, std::size_t> info_pack;
    }



    template<typename... T, typename... E>
    inline bool report(std::ostream& os, bool success
                      ,std::tuple<E...> const& exps
                      ,info_pack const& inf)
    {
        if (success)
            os << " PASS ";
        else
            os << "-FAIL " << std::get<1>(inf) << ":" << std::get<2>(inf) << ": ";

        os << std::get<0>(inf) << " " << exps << std::endl;
        return success;
    }


    inline void assert_(bool b)
    {
        if (!b)
        {
            std::cout << "assertion failure. exiting" << std::endl;
            exit(1);
        }
    }


    template<typename F, typename... T, typename... E>
    inline bool check(F const& f, std::tuple<T...> const& args
                     ,std::tuple<E...> const& exps
                     ,info_pack const& inf)
    {
        return report(std::cout, apply(f, args), exps, inf);
    }




} }
