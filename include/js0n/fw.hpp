#pragma once

#include <string>
//#include <vector>
#include <deque>

namespace vrac0x { namespace js0n
{

    struct k;

    struct val;


    typedef std::string string;

    typedef std::pair<string, val> pair;

//TODO make it parameterizable
//    typedef std::vector<pair> object;
//    typedef std::vector<val> array;
    typedef std::deque<pair> object;
    typedef std::deque<val> array;

    struct null_type;
    struct empty_array_type;
    struct empty_object_type;

    enum class type_info : unsigned int;


    template<typename U>
    U& get(val&);

    template<typename U>
    U const& get(val const&);

    template<typename U>
    U* get(val*);

    template<typename U>
    U const* get(val const*);


    template<typename U>
    bool operator==(val const&, U const&);

    template<typename U>
    bool operator==(U const&, val const&);

    bool operator==(val const&, null_type);
    bool operator==(null_type, val const&);

    template<typename U>
    bool operator!=(val const&, U const&);

    template<typename U>
    bool operator!=(U const&, val const&);


    namespace detail
    {
        template<typename>
        struct type_to_mem;

        template<typename>
        struct iter;
    }

    typedef detail::iter<val> iterator;
    typedef detail::iter<val const> const_iterator;

} }
