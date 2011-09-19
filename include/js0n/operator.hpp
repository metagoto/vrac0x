#pragma once


namespace vrac0x { namespace js0n
{


    namespace detail
    {

        template<>
        struct type_to_mem<int>
        {
            template<typename T>
            static typename std::conditional<
                std::is_const<T>::value, int const*, int*
            >::type
            get(T& v)
            {
                if (v.type() == type_info::int_)
                    return &v.i_;
                return nullptr;
            }
        };


        template<>
        struct type_to_mem<double>
        {
            template<typename T>
            static typename std::conditional<
                std::is_const<T>::value, double const*, double*
            >::type
            get(T& v)
            {
                if (v.type() == type_info::double_)
                    return &v.d_;
                return nullptr;
            }
        };


        template<>
        struct type_to_mem<bool>
        {
            template<typename T>
            static typename std::conditional<
                std::is_const<T>::value, bool const*, bool*
            >::type
            get(T& v)
            {
                if (v.type() == type_info::bool_)
                    return &v.b_;
                return nullptr;
            }
        };


        template<>
        struct type_to_mem<std::string>
        {
            template<typename T>
            static typename std::conditional<
                std::is_const<T>::value, std::string const*, std::string*
            >::type
            get(T& v)
            {
                if (v.type() == type_info::string)
                    return &v.s_;
                return nullptr;
            }
        };


        template<>
        struct type_to_mem<object>
        {
            template<typename T>
            static typename std::conditional<
                std::is_const<T>::value, object const*, object*
            >::type
            get(T& v)
            {
                if (v.type() == type_info::object)
                    return &v.o_;
                return nullptr;
            }
        };


        template<>
        struct type_to_mem<array>
        {
            template<typename T>
            static typename std::conditional<
                std::is_const<T>::value, array const*, array*
            >::type
            get(T& v)
            {
                if (v.type() == type_info::array)
                    return &v.a_;
                return nullptr;
            }
        };


        // TODO wtf specialization
        template<>
        struct type_to_mem<char const>
        {
            template<typename T>
            static char const*
            get(T& v)
            {
                if (v.type() == type_info::string)
                    return const_cast<val const&>(v).s_.c_str();
                return nullptr;
            }
        };
    }



    template<typename U>
    inline U& get(val& v)
    {
        U* u = detail::type_to_mem<U>::get(v);
        if (u)
            return *u;
        throw std::invalid_argument("bad type request");
    }


    template<typename U>
    inline U const& get(val const& v)
    {
        U const* u = detail::type_to_mem<U>::get(v);
        if (u)
            return *u;
        throw std::invalid_argument("bad type request");
    }


    template<typename U>
    inline U* get(val* v)
    {
        return v ? detail::type_to_mem<U>::get(*v) : nullptr;
    }


    template<typename U>
    inline U const* get(val const* v)
    {
        return v ? detail::type_to_mem<U>::get(*v) : nullptr;
    }


    template<typename U>
    inline bool operator==(val const& v, U const& u)
    {
        U const* t = detail::type_to_mem<U>::get(v);
        if (t)
            return *t == u;
        return false;
    }


    template<typename U>
    inline bool operator==(U const& u, val const& v)
    {
        return v == u;
    }


    inline bool operator==(val const& v, null_type)
    {
        return v.type() == type_info::null;
    }


    inline bool operator==(null_type, val const& v)
    {
        return v.type() == type_info::null;
    }


    template<typename U>
    inline bool operator!=(val const& v, U const& u)
    {
        return !(v == u);
    }


    template<typename U>
    inline bool operator!=(U const& u, val const& v)
    {
        return !(v == u);
    }



} }
