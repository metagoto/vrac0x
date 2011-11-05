#pragma once

#include <algorithm>
#include <stdexcept>


namespace vrac0x { namespace js0n
{

    template<typename T>
    constexpr inline basic_val<T>::k::k(char_type const* s)
        : key(s)
    { }


    template<typename T>
    constexpr inline typename basic_val<T>::pair
    basic_val<T>::k::operator=(array const& a)
    {
        return pair(key, a);
    }


    template<typename T>
    template<typename U>
    constexpr inline typename
    std::enable_if<
        !std::is_same<U,std::initializer_list<typename basic_val<T>::pair>>::value
        ,typename basic_val<T>::pair
    >::type basic_val<T>::k::operator=(U&& t)
    {
        return pair(key, std::forward<U>(t));
    }


    template<typename T>
    constexpr inline typename basic_val<T>::pair
    basic_val<T>::k::operator=(std::initializer_list<pair> list)
    {
        return pair(key, list);
    }


    ///


    template<typename T>
    constexpr inline basic_val<T>::basic_val()
        //: type_(type_info::null) // used to be
        //: basic_val(empty_object_type()) // waiting for constructor delegation
        : type_(type_info::object)
        , o_()
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(basic_val<T>::char_type const* s)
        : type_(type_info::string)
        , s_(s)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(string const& s)
        : type_(type_info::string)
        , s_(s)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(basic_val<T>::int_type i)
        : type_(type_info::int_)
        , i_(i)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(basic_val<T>::float_type d)
        : type_(type_info::double_)
        , d_(d)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(bool b)
        : type_(type_info::bool_)
        , b_(b)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(null_type)
        : type_(type_info::null)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(empty_array_type)
        : type_(type_info::array)
        , a_()
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(empty_object_type)
        : type_(type_info::object)
        , o_()
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(array const& a)
        : type_(type_info::array)
        , a_(a)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(object const& o)
        : type_(type_info::object)
        , o_(o)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(string&& s)
        : type_(type_info::string)
        , s_(std::move(s))
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(array&& a)
        : type_(type_info::array)
        , a_(std::move(a))
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(object&& o)
        : type_(type_info::object)
        , o_(std::move(o))
    { }


    template<typename T>
    template<typename U, typename>
    constexpr inline basic_val<T>::basic_val(U t)
        : type_(type_info::int_) // TODO constructor delegation
        , i_(t)
    { }


    template<typename T>
    template<typename U, typename, typename>
    constexpr inline basic_val<T>::basic_val(U t)
        : type_(type_info::double_)
        , d_(t)
    { }


    template<typename T>
    inline basic_val<T>::basic_val(std::initializer_list<pair> list)
        : type_(type_info::object)
        , o_(list.size())
    {
        std::copy(list.begin(), list.end(), o_.begin());
    }


    template<typename T>
    inline basic_val<T>::basic_val(std::initializer_list<self_type> list)
        : type_(type_info::array)
        , a_(list.size())
    {
        std::copy(list.begin(), list.end(), a_.begin());
    }


    template<typename T>
    inline basic_val<T>::basic_val(self_type const& o)
        : type_(type_info::undefined)
    {
        copy(o);
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator=(self_type const& o)
    {
        if (this != &o)
            copy(o);
        return *this;
    }


    template<typename T>
    inline basic_val<T>::basic_val(self_type&& o)
        : type_(type_info::undefined)
    {
        move(std::move(o));
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator=(self_type&& o)
    {
        move(std::move(o));
        return *this;
    }


    template<typename T>
    inline basic_val<T>::~basic_val()
    {
        free();
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator[](std::size_t i)
    {
        if (type() != type_info::array)
            throw std::invalid_argument("not an array");

        if (i >= a_.size())
            a_.resize(i+1);

        return a_[i];
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator[](string const& s)
    {
        if (type() != type_info::object)
            throw std::invalid_argument("not an object");

        auto it = std::find_if(o_.begin(), o_.end(), [&s](pair const& p){
            return p.first == s;
        });

        if (it != o_.end())
            return it->second;

        o_.push_back(pair(s, null_type()));
        return o_.back().second;
    }


    template<typename T>
    template<std::size_t N>
    inline basic_val<T>& basic_val<T>::operator[](char_type const(&s)[N])
    {
        return this->operator[](string(s));
    }


    template<typename T>
    inline basic_val<T> const& basic_val<T>::operator[](std::size_t i) const
    {
        if (type() != type_info::array)
            throw std::invalid_argument("not an array");

        if (i >= a_.size())
            throw std::out_of_range();

        return a_[i];
    }


    template<typename T>
    inline basic_val<T> const& basic_val<T>::operator[](string const& s) const
    {
        if (type() != type_info::object)
            throw std::invalid_argument("not an object");

        auto it = std::find_if(o_.begin(), o_.end(), [&s](pair const& p){
            return p.first == s;
        });

        if (it != o_.end())
            return it->second;

        throw std::out_of_range(s);
    }


    template<typename T>
    template<std::size_t N>
    inline basic_val<T> const& basic_val<T>::operator[](char_type const(&s)[N]) const
    {
        return this->operator[](string(s));
    }


    template<typename T>
    template<typename U>
    inline basic_val<T>::operator U() const
    {
        return *get<U>(this);
    }


    template<typename T>
    inline basic_val<T>::operator char_type const*() const
    {
        return get<char_type const>(this);
    }


    template<typename T>
    inline bool basic_val<T>::operator==(self_type const& v) const
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
        return true;
    }


    template<typename T>
    inline bool basic_val<T>::operator!=(self_type const& v) const
    {
        return !this->operator==(v);
    }


    // TODO redo/refactor/rethink
    template<typename T>
    inline std::size_t basic_val<T>::size() const
    {
        if (type() == type_info::object)
            return o_.size();
        if (type() == type_info::array)
            return a_.size();
        if (type() == type_info::string)
            return s_.size();
        return 0;
    }


    template<typename T>
    inline type_info basic_val<T>::type() const
    {
        return type_;
    }


    template<typename T>
    inline void basic_val<T>::copy(self_type const& o)
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


    template<typename T>
    inline void basic_val<T>::free()
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


    template<typename T>
    inline void basic_val<T>::move(self_type&& o)
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
