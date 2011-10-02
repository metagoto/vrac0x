#pragma once

#include <type_traits>
#include <initializer_list>


namespace vrac0x { namespace js0n
{

    template<typename Tag>
    struct basic_val
    {

        typedef Tag            tag;
        typedef basic_val<tag> self_type;

        typedef typename traits<self_type,tag>::string_type string;
        typedef typename traits<self_type,tag>::pair_type   pair;
        typedef typename traits<self_type,tag>::array_type  array;
        typedef typename traits<self_type,tag>::object_type object;
        typedef typename traits<self_type,tag>::char_type   char_type;
        typedef typename traits<self_type,tag>::int_type    int_type;
        typedef typename traits<self_type,tag>::float_type  float_type;

        typedef detail::iter<self_type>       iterator;
        typedef detail::iter<self_type const> const_iterator;


        struct k
        {
            constexpr explicit k(char_type const*);

            constexpr pair operator=(array const&);

            template<typename T>
            constexpr typename std::enable_if<
                !std::is_same<T,std::initializer_list<pair>>::value
                ,pair
            >::type operator=(T&&);

            constexpr pair operator=(std::initializer_list<pair>);

            char_type const* const key;
        };


        constexpr basic_val();
        constexpr basic_val(int_type);
        constexpr basic_val(float_type);
        constexpr basic_val(bool);
        constexpr basic_val(char_type const*);
        constexpr basic_val(string const&);
        constexpr basic_val(null_type);
        constexpr basic_val(empty_array_type);
        constexpr basic_val(empty_object_type);
        constexpr basic_val(array const&);

        basic_val(std::initializer_list<pair>);
        basic_val(std::initializer_list<self_type>);

        basic_val(self_type const&);
        self_type& operator=(self_type const&);

        basic_val(self_type&&);
        self_type& operator=(self_type&&);

        //// type coercion for arithmetic types (tmp)
        //// TODO better integration with traits. excluse irrelevant ops
        template<typename T, typename std::enable_if<
            std::is_integral<T>::value,void>::type* = nullptr
        >
        constexpr inline basic_val(T t)
            : type_(type_info::int_) // TODO constructor delegation
            , i_(t)
        { }

        template<typename T, typename std::enable_if<
            std::is_floating_point<T>::value,void>::type* = nullptr
        >
        constexpr inline basic_val(T t)
            : type_(type_info::double_)
            , d_(t)
        { }
        ////

        ~basic_val();

        self_type& operator[](std::size_t);
        self_type const& operator[](std::size_t) const;

        self_type& operator[](string const&);
        self_type const& operator[](string const&) const;

        template<std::size_t N>
        self_type& operator[](char_type const(&)[N]);
        template<std::size_t N>
        self_type const& operator[](char_type const(&)[N]) const;

        template<typename T>
        operator T() const;
        operator char_type const*() const;

        bool operator==(self_type const&) const;
        bool operator!=(self_type const&) const;

        type_info type() const;

        std::size_t size() const;


    private:

        type_info type_;

        union {
            object     o_;
            array      a_;
            string     s_;
            int_type   i_;
            float_type d_;
            bool       b_;
        };


        void copy(self_type const&);
        void move(self_type&&);
        void free();

        template<typename>
        friend struct detail::iter;

        template<typename,typename>
        friend struct detail::type_to_mem;


    };


} }
