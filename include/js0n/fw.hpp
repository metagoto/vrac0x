#pragma once


namespace vrac0x { namespace js0n
{

    template<typename, typename>
    struct traits;

    template<typename, typename>
    struct basic_val;

    struct null_type;
    struct empty_array_type;
    struct empty_object_type;

    enum class type_info : unsigned int;


    template<typename U, typename S, typename C>
    U& get(basic_val<S,C>&);

    template<typename U, typename S, typename C>
    U const& get(basic_val<S,C> const&);

    template<typename U, typename S, typename C>
    U* get(basic_val<S,C>*);

    template<typename U, typename S, typename C>
    U const* get(basic_val<S,C> const*);


    template<typename U, typename S, typename C>
    bool operator==(basic_val<S,C> const&, U const&);

    template<typename U, typename S, typename C>
    bool operator==(U const&, basic_val<S,C> const&);

    template<typename S, typename C>
    bool operator==(basic_val<S,C> const&, null_type);

    template<typename S, typename C>
    bool operator==(null_type, basic_val<S,C> const&);

    template<typename U, typename S, typename C>
    bool operator!=(basic_val<S,C> const&, U const&);

    template<typename U, typename S, typename C>
    bool operator!=(U const&, basic_val<S,C> const&);


    namespace detail
    {
        template<typename,typename>
        struct type_to_mem;

        template<typename>
        struct iter;
    }

} }
