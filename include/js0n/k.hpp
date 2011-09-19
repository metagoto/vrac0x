#pragma once



namespace vrac0x { namespace js0n
{

    struct k
    {
        k(char const*);

        pair operator=(array const&);

        template<typename T>
        pair operator=(T&&);

        template<typename T>
        pair operator=(std::initializer_list<T>);

        char const* const key;
    };



} }
