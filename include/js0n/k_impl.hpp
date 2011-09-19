#pragma once



namespace vrac0x { namespace js0n
{


    inline k::k(char const* s)
        : key(s)
    { }


    inline pair k::operator=(array const& a)
    {
        return pair(key, a);
    }


    template<typename T>
    inline pair k::operator=(T&& t)
    {
        return pair(key, std::forward<T>(t));
    }


    template<typename T>
    inline pair k::operator=(std::initializer_list<T> list)
    {
        return pair(key, list);
    }


} }
