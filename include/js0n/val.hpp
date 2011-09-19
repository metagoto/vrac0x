#pragma once


namespace vrac0x { namespace js0n
{


    struct val
    {

        val();

        val(int);
        val(double);
        val(bool);
        val(char const*);
        val(string const&);
        val(null_type);
        val(empty_array_type);
        val(empty_object_type);

        val(array const&);
        val(std::initializer_list<pair>);
        val(std::initializer_list<val>);

        val(val const&);
        val& operator=(val const&);

        val(val&&);
        val& operator=(val&&);

        // TODO add operator=(POD)

        ~val();

        val& operator[](size_t);
        val& operator[](string const&);
        template<size_t N>
        val& operator[](char const(&)[N]);

        val const& operator[](size_t) const;
        val const& operator[](string const&) const;
        template<size_t N>
        val const& operator[](char const(&)[N]) const;

        // not sure we need this
        template<typename T>
        inline operator T() const;

        bool operator==(val const&) const;
        bool operator!=(val const&) const;

        type_info type() const;


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


        void copy(val const&);
        void move(val&&);
        void free();

        template<typename>
        friend struct detail::iter;

        template<typename>
        friend struct detail::type_to_mem;


    };


} }
