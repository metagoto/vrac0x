#pragma once

#include <iostream>

#include "../unpack.hpp"
#include "../tupility.hpp"


namespace vrac0x { namespace testiculs
{


    template<typename... T, typename... E>
    static void report(bool success, std::tuple<T...> const& args
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
    static void check(F const& f, std::tuple<T...> const& args
                     ,std::tuple<E...> const& exps
                     ,char const* test, char const* file, std::size_t line)
    {
        if (unpack_apply(f, args))
            report(true, args, exps, test, file, line);
        else
            report(false, args, exps, test, file, line);

    }


    template<typename F, typename... T, typename... E>
    static void assert(F const& f, std::tuple<T...> const& args
                      ,std::tuple<E...> const& exps
                      ,char const* test, char const* file, std::size_t line)
    {
        if (unpack_apply(f, args))
            report(true, args, exps, test, file, line);
        else {
            report(false, args, exps, test, file, line);
            std::cout << "exiting" << std::endl;
            exit(1);
        }
    }




} }
