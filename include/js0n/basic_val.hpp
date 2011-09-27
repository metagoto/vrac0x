#pragma once


namespace vrac0x { namespace js0n
{

    template<typename StrTag, typename ConTag>
    struct basic_val
    {

        typedef basic_val<StrTag,ConTag> self_type;
        typedef typename traits<self_type,StrTag>::string_type string;
        typedef typename traits<self_type,ConTag>::pair_type   pair;
        typedef typename traits<self_type,ConTag>::array_type  array;
        typedef typename traits<self_type,ConTag>::object_type object;
        typedef typename traits<self_type,StrTag>::char_type   char_type;

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
        constexpr basic_val(int);
        constexpr basic_val(double);
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

        // TODO add operator=(POD)

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
            object o_;
            array  a_;
            string s_;
            int    i_;
            double d_;
            bool   b_;
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
