#pragma once

namespace vrac0x { namespace js0n
{

    struct val
    {

        val();

        val(char const*);
        val(string const&);
        val(int);
        val(double);
        val(bool);
        val(null_type);

        val(array const&);
        val(std::initializer_list<pair>);
        val(std::initializer_list<val>);

        val(val const&);
        val& operator=(val const&);

        val(val&&);
        val& operator=(val&&);

        ~val();

        void copy(val const&);
        void move(val&&);
        void free();


        type type_;

        union {
            object o_;
            array  a_;
            string s_;
            int    i_;
            double d_;
            bool   b_;
        };

    };


    ////////


    inline val::val()
        : type_(type::null)
    { }


    inline val::val(char const* s)
        : type_(type::string)
        , s_(s)
    { }


    inline val::val(string const& s)
        : type_(type::string)
        , s_(s)
    { }


    inline val::val(int i)
        : type_(type::int_)
        , i_(i)
    { }


    inline val::val(double d)
        : type_(type::double_)
        , d_(d)
    { }


    inline val::val(bool b)
        : type_(type::bool_)
        , b_(b)
    { }


    inline val::val(null_type)
        : type_(type::null)
    { }


    inline val::val(array const& a)
        : type_(type::array)
        , a_(a)
    { }


    inline val::val(std::initializer_list<pair> list)
        : type_(type::object)
        , o_(list.size())
    {
        std::copy(list.begin(), list.end(), o_.begin());
    }


    inline val::val(std::initializer_list<val> list)
        : type_(type::array)
        , a_(list.size())
    {
        std::copy(list.begin(), list.end(), a_.begin());
    }


    inline val::val(val const& o)
        : type_(type::undefined)
    {
        copy(o);
    }


    inline val& val::operator=(val const& o)
    {
        if (this != &o)
            copy(o);
        return *this;
    }


    inline val::val(val&& o)
        : type_(type::undefined)
    {
        move(std::move(o));
    }


    inline val& val::operator=(val&& o)
    {
        move(std::move(o));
        return *this;
    }


    inline val::~val()
    {
        free();
    }


    inline void val::copy(val const& o)
    {
        if (type_ == o.type_)
        {
            switch (o.type_)
            {
                case type::object:
                    o_ = o.o_;
                    break;
                case type::array:
                    a_ = o.a_;
                    break;
                case type::string:
                    s_ = o.s_;
                    break;
                case type::int_:
                    i_ = o.i_;
                    break;
                case type::double_:
                    d_ = o.d_;
                    break;
                case type::bool_:
                    b_ = o.b_;
                    break;
                default:
                    break;
            }
            return;
        }

        free();

        switch (type_ = o.type_)
        {
            case type::object:
                new (&o_) object(o.o_);
                break;
            case type::array:
                new (&a_) array(o.a_);
                break;
            case type::string:
                new (&s_) string(o.s_);
                break;
            case type::int_:
                i_ = o.i_;
                break;
            case type::double_:
                d_ = o.d_;
                break;
            case type::bool_:
                b_ = o.b_;
                break;
            default:
                break;
        }

    }


    inline void val::free()
    {
        switch (type_)
        {
            case type::object:
                o_.~object();
                break;
            case type::array:
                a_.~array();
                break;
            case type::string:
                s_.~string();
                break;
            default:
                break;
        }

        type_= type::undefined;
    }


    inline void val::move(val&& o)
    {
        if (type_ == o.type_)
        {
            switch (o.type_)
            {
                case type::object:
                    o_ = std::move(o.o_);
                    break;
                case type::array:
                    a_ = std::move(o.a_);
                    break;
                case type::string:
                    s_ = std::move(o.s_);
                    break;
                case type::int_:
                    i_ = o.i_;
                    break;
                case type::double_:
                    d_ = o.d_;
                    break;
                case type::bool_:
                    b_ = o.b_;
                    break;
                default:
                    break;
            }
            return;
        }

        free();

        switch (type_ = o.type_)
        {
            case type::object:
                new (&o_) object(std::move(o.o_));
                break;
            case type::array:
                new (&a_) array(std::move(o.a_));
                break;
            case type::string:
                new (&s_) string(std::move(o.s_));
                break;
            case type::int_:
                i_ = o.i_;
                break;
            case type::double_:
                d_ = o.d_;
                break;
            case type::bool_:
                b_ = o.b_;
                break;
            default:
                break;
        }
    }



} }
