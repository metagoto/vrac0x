#pragma once

#include <algorithm>
#include <stdexcept>


namespace vrac0x { namespace js0n
{

    inline val::val()
        : type_(type_info::null)
    { }


    inline val::val(char const* s)
        : type_(type_info::string)
        , s_(s)
    { }


    inline val::val(string const& s)
        : type_(type_info::string)
        , s_(s)
    { }


    inline val::val(int i)
        : type_(type_info::int_)
        , i_(i)
    { }


    inline val::val(double d)
        : type_(type_info::double_)
        , d_(d)
    { }


    inline val::val(bool b)
        : type_(type_info::bool_)
        , b_(b)
    { }


    inline val::val(null_type)
        : type_(type_info::null)
    { }


    inline val::val(empty_array_type)
        : type_(type_info::array)
        , a_()
    { }


    inline val::val(empty_object_type)
        : type_(type_info::object)
        , o_()
    { }


    inline val::val(array const& a)
        : type_(type_info::array)
        , a_(a)
    { }


    inline val::val(std::initializer_list<pair> list)
        : type_(type_info::object)
        , o_(list.size())
    {
        std::copy(list.begin(), list.end(), o_.begin());
    }


    inline val::val(std::initializer_list<val> list)
        : type_(type_info::array)
        , a_(list.size())
    {
        std::copy(list.begin(), list.end(), a_.begin());
    }


    inline val::val(val const& o)
        : type_(type_info::undefined)
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
        : type_(type_info::undefined)
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


    inline val& val::operator[](unsigned int i)
    {
        if (type() != type_info::array)
            throw std::invalid_argument("not an array");

        return a_.at(i); // may throw. no insertion (for now?)
    }


    inline val& val::operator[](string const& s)
    {
        if (type() != type_info::object)
            throw std::invalid_argument("not an object");

        auto it = std::find_if(o_.begin(), o_.end(), [s](pair const& p){
            return p.first == s;
        });

        if (it != o_.end())
            return it->second;

        // same as std::map. insert if non existent
        o_.push_back(pair(s, null_type()));
        return o_.at(o_.size()-1).second;
    }


    template<size_t N>
    inline val& val::operator[](char const(&s)[N])
    {
       return this->operator[](string(s));
    }


    template<typename T>
    inline val::operator T() const
    {
        return *get<T>(this);
    }


    //TODO wtf specialization
    template<>
    inline val::operator char const*() const
    {
        return get<char const>(this);
    }


    inline bool val::operator==(val const& v) const
    {
        if (type() != v.type())
            return false;

        switch (type())
        {
            case type_info::object:
                return o_ == v.o_;
            case type_info::array:
                return a_ == v.a_;
            case type_info::string:
                return s_ == v.s_;
            case type_info::int_:
                return i_ == v.i_;
            case type_info::double_:
                return d_ == v.d_;
            case type_info::bool_:
                return b_ == v.b_;
            default:
                break;
        }
        return false;
    }


    inline bool val::operator!=(val const& v) const
    {
        return !this->operator==(v);
    }


    inline type_info val::type() const
    {
        return type_;
    }


    inline void val::copy(val const& o)
    {
        if (type() == o.type())
        {
            switch (o.type())
            {
                case type_info::object:
                    o_ = o.o_;
                    break;
                case type_info::array:
                    a_ = o.a_;
                    break;
                case type_info::string:
                    s_ = o.s_;
                    break;
                case type_info::int_:
                    i_ = o.i_;
                    break;
                case type_info::double_:
                    d_ = o.d_;
                    break;
                case type_info::bool_:
                    b_ = o.b_;
                    break;
                default:
                    break;
            }
            return;
        }

        free();

        switch (type_ = o.type())
        {
            case type_info::object:
                new (&o_) object(o.o_);
                break;
            case type_info::array:
                new (&a_) array(o.a_);
                break;
            case type_info::string:
                new (&s_) string(o.s_);
                break;
            case type_info::int_:
                i_ = o.i_;
                break;
            case type_info::double_:
                d_ = o.d_;
                break;
            case type_info::bool_:
                b_ = o.b_;
                break;
            default:
                break;
        }
    }


    inline void val::free()
    {
        switch (type())
        {
            case type_info::object:
                o_.~object();
                break;
            case type_info::array:
                a_.~array();
                break;
            case type_info::string:
                s_.~string();
                break;
            default:
                break;
        }

        type_= type_info::undefined;
    }


    inline void val::move(val&& o)
    {
        if (type() == o.type())
        {
            switch (o.type())
            {
                case type_info::object:
                    o_ = std::move(o.o_);
                    break;
                case type_info::array:
                    a_ = std::move(o.a_);
                    break;
                case type_info::string:
                    s_ = std::move(o.s_);
                    break;
                case type_info::int_:
                    i_ = o.i_;
                    break;
                case type_info::double_:
                    d_ = o.d_;
                    break;
                case type_info::bool_:
                    b_ = o.b_;
                    break;
                default:
                    break;
            }
            return;
        }

        free();

        switch (type_ = o.type())
        {
            case type_info::object:
                new (&o_) object(std::move(o.o_));
                break;
            case type_info::array:
                new (&a_) array(std::move(o.a_));
                break;
            case type_info::string:
                new (&s_) string(std::move(o.s_));
                break;
            case type_info::int_:
                i_ = o.i_;
                break;
            case type_info::double_:
                d_ = o.d_;
                break;
            case type_info::bool_:
                b_ = o.b_;
                break;
            default:
                break;
        }
    }





} }
