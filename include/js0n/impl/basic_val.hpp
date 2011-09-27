#pragma once

#include <algorithm>
#include <stdexcept>


namespace vrac0x { namespace js0n
{

    template<typename S, typename C>
    constexpr inline basic_val<S,C>::k::k(char_type const* s)
        : key(s)
    { }


    template<typename S, typename C>
    constexpr inline typename basic_val<S,C>::pair
    basic_val<S,C>::k::operator=(array const& a)
    {
        return pair(key, a);
    }


    template<typename S, typename C>
    template<typename T>
    constexpr inline typename
    std::enable_if<
        !std::is_same<T,std::initializer_list<typename basic_val<S,C>::pair>>::value
        ,typename basic_val<S,C>::pair
    >::type basic_val<S,C>::k::operator=(T&& t)
    {
        return pair(key, std::forward<T>(t));
    }


    template<typename S, typename C>
    constexpr inline typename basic_val<S,C>::pair
    basic_val<S,C>::k::operator=(std::initializer_list<pair> list)
    {
        return pair(key, list);
    }


    ///


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val()
        //: type_(type_info::null) // used to be
        //: basic_val(empty_object_type()) // waiting for constructor delegation
        : type_(type_info::object)
        , o_()
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(basic_val<S,C>::char_type const* s)
        : type_(type_info::string)
        , s_(s)
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(string const& s)
        : type_(type_info::string)
        , s_(s)
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(int i)
        : type_(type_info::int_)
        , i_(i)
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(double d)
        : type_(type_info::double_)
        , d_(d)
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(bool b)
        : type_(type_info::bool_)
        , b_(b)
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(null_type)
        : type_(type_info::null)
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(empty_array_type)
        : type_(type_info::array)
        , a_()
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(empty_object_type)
        : type_(type_info::object)
        , o_()
    { }


    template<typename S, typename C>
    constexpr inline basic_val<S,C>::basic_val(array const& a)
        : type_(type_info::array)
        , a_(a)
    { }


    template<typename S, typename C>
    inline basic_val<S,C>::basic_val(std::initializer_list<pair> list)
        : type_(type_info::object)
        , o_(list.size())
    {
        std::copy(list.begin(), list.end(), o_.begin());
    }


    template<typename S, typename C>
    inline basic_val<S,C>::basic_val(std::initializer_list<self_type> list)
        : type_(type_info::array)
        , a_(list.size())
    {
        std::copy(list.begin(), list.end(), a_.begin());
    }


    template<typename S, typename C>
    inline basic_val<S,C>::basic_val(self_type const& o)
        : type_(type_info::undefined)
    {
        copy(o);
    }


    template<typename S, typename C>
    inline basic_val<S,C>& basic_val<S,C>::operator=(self_type const& o)
    {
        if (this != &o)
            copy(o);
        return *this;
    }


    template<typename S, typename C>
    inline basic_val<S,C>::basic_val(self_type&& o)
        : type_(type_info::undefined)
    {
        move(std::move(o));
    }


    template<typename S, typename C>
    inline basic_val<S,C>& basic_val<S,C>::operator=(self_type&& o)
    {
        move(std::move(o));
        return *this;
    }


    template<typename S, typename C>
    inline basic_val<S,C>::~basic_val()
    {
        free();
    }


    template<typename S, typename C>
    inline basic_val<S,C>& basic_val<S,C>::operator[](std::size_t i)
    {
        if (type() != type_info::array)
            throw std::invalid_argument("not an array");

        return a_.at(i); // may throw. no insertion (for now?)
    }


    template<typename S, typename C>
    inline basic_val<S,C>& basic_val<S,C>::operator[](string const& s)
    {
        if (type() != type_info::object)
            throw std::invalid_argument("not an object");

        auto it = std::find_if(o_.begin(), o_.end(), [&s](pair const& p){
            return p.first == s;
        });

        if (it != o_.end())
            return it->second;

        // same as std::map. insert if non existent
        o_.push_back(pair(s, null_type()));
        return o_.at(o_.size()-1).second;
    }


    template<typename S, typename C>
    template<std::size_t N>
    inline basic_val<S,C>& basic_val<S,C>::operator[](char_type const(&s)[N])
    {
        return this->operator[](string(s));
    }


    template<typename S, typename C>
    inline basic_val<S,C> const& basic_val<S,C>::operator[](std::size_t i) const
    {
        return const_cast<self_type const&>(const_cast<self_type*>(this)->operator[](i));
    }


    template<typename S, typename C>
    inline basic_val<S,C> const& basic_val<S,C>::operator[](string const& s) const
    {
        return const_cast<self_type const&>(const_cast<self_type*>(this)->operator[](s));
    }


    template<typename S, typename C>
    template<std::size_t N>
    inline basic_val<S,C> const& basic_val<S,C>::operator[](char_type const(&s)[N]) const
    {
        return const_cast<self_type const&>(const_cast<self_type*>(this)->operator[](string(s)));
    }


    template<typename S, typename C>
    template<typename T>
    inline basic_val<S,C>::operator T() const
    {
        return *get<T>(this);
    }


    template<typename S, typename C>
    inline basic_val<S,C>::operator char_type const*() const
    {
        return get<char_type const>(this);
    }


    template<typename S, typename C>
    inline bool basic_val<S,C>::operator==(self_type const& v) const
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


    template<typename S, typename C>
    inline bool basic_val<S,C>::operator!=(self_type const& v) const
    {
        return !this->operator==(v);
    }


    // TODO redo/refactor/rethink
    template<typename S, typename C>
    inline std::size_t basic_val<S,C>::size() const
    {
        if (type() == type_info::object)
            return o_.size();
        if (type() == type_info::array)
            return a_.size();
        if (type() == type_info::string)
            return s_.size();
        return 0;
    }


    template<typename S, typename C>
    inline type_info basic_val<S,C>::type() const
    {
        return type_;
    }


    template<typename S, typename C>
    inline void basic_val<S,C>::copy(self_type const& o)
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


    template<typename S, typename C>
    inline void basic_val<S,C>::free()
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


    template<typename S, typename C>
    inline void basic_val<S,C>::move(self_type&& o)
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
