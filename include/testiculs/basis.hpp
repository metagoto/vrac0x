#pragma once

#include <iostream>

#include "../unpack.hpp"
#include "../tupility.hpp"


namespace vrac0x { namespace testiculs
{


    template<typename... T, typename... E>
    inline void report(bool success, std::tuple<T...> const& args
                      ,std::tuple<E...> const& exps
                      ,char const* test, char const* file, std::size_t line)
    {
        if (success)
            std::cout << " PASS ";
        else
            std::cout << "-FAIL " << file << ":" << line << ": ";

        std::cout << test << " " << exps << std::endl;
    }


    template<typename F, typename... T, typename... E>
    inline bool check(F const& f, std::tuple<T...> const& args
                     ,std::tuple<E...> const& exps
                     ,char const* test, char const* file, std::size_t line)
    {
        bool success = unpack_apply(f, args);
        report(success, args, exps, test, file, line);
        return success;
    }


    inline void assert_(bool b)
    {
        if (!b)
        {
            std::cout << "exiting" << std::endl;
            exit(1);
        }
    }



} }
