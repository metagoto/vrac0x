#pragma once


namespace vrac0x { namespace js0n
{


    namespace detail
    {

        template<typename V>
        struct type_to_mem<V, int>
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


        template<typename V>
        struct type_to_mem<V, double>
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


        template<typename V>
        struct type_to_mem<V, bool>
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


        template<typename V>
        struct type_to_mem<V, typename V::string>
        {
            typedef typename V::string string;

            template<typename T>
            static typename std::conditional<
                std::is_const<T>::value, string const*, string*
            >::type
            get(T& v)
            {
                if (v.type() == type_info::string)
                    return &v.s_;
                return nullptr;
            }
        };


        template<typename V>
        struct type_to_mem<V, typename V::object>
        {
            typedef typename V::object object;

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


        template<typename V>
        struct type_to_mem<V, typename V::array>
        {
            typedef typename V::array array;

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
        template<typename V>
        struct type_to_mem<V, typename V::char_type const>
        {
            template<typename T>
            static typename V::char_type const*
            get(T& v)
            {
                if (v.type() == type_info::string)
                    return const_cast<V const&>(v).s_.c_str();
                return nullptr;
            }
        };

    }



    template<typename U, typename S, typename C>
    inline U& get(basic_val<S,C>& v)
    {
        U* u = detail::type_to_mem<basic_val<S,C>,U>::get(v);
        if (u)
            return *u;
        throw std::invalid_argument("bad type request");
    }


    template<typename U, typename S, typename C>
    inline U const& get(basic_val<S,C> const& v)
    {
        U const* u = detail::type_to_mem<basic_val<S,C>,U>::get(v);
        if (u)
            return *u;
        throw std::invalid_argument("bad type request");
    }


    template<typename U, typename S, typename C>
    inline U* get(basic_val<S,C>* v)
    {
        return v ? detail::type_to_mem<basic_val<S,C>,U>::get(*v) : nullptr;
    }


    template<typename U, typename S, typename C>
    inline U const* get(basic_val<S,C> const* v)
    {
        return v ? detail::type_to_mem<basic_val<S,C>,U>::get(*v) : nullptr;
    }


    template<typename U, typename S, typename C>
    inline bool operator==(basic_val<S,C> const& v, U const& u)
    {
        U const* t = detail::type_to_mem<basic_val<S,C>,U>::get(v);
        if (t)
            return *t == u;
        return false;
    }


    template<typename U, typename S, typename C>
    inline bool operator==(U const& u, basic_val<S,C> const& v)
    {
        return v == u;
    }


    template<typename S, typename C>
    inline bool operator==(basic_val<S,C> const& v, null_type)
    {
        return v.type() == type_info::null;
    }


    template<typename S, typename C>
    inline bool operator==(null_type, basic_val<S,C> const& v)
    {
        return v.type() == type_info::null;
    }


    template<typename U, typename S, typename C>
    inline bool operator!=(basic_val<S,C> const& v, U const& u)
    {
        return !(v == u);
    }


    template<typename U, typename S, typename C>
    inline bool operator!=(U const& u, basic_val<S,C> const& v)
    {
        return !(v == u);
    }



} }
