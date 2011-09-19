#pragma once

#include <memory>


namespace vrac0x { namespace js0n
{

    namespace detail
    {


        struct iter_impl_base
        {
            virtual ~iter_impl_base() {}
            virtual bool operator!=(iter_impl_base const&) const = 0;
            virtual iter_impl_base& operator++() = 0;
            virtual iter_impl_base& operator+(std::size_t i) = 0;
            virtual val const& operator*() const = 0;
            virtual val& operator*() = 0;
        };


        template<typename T>
        struct iter_impl : public iter_impl_base
        {

            typedef T container_type;
            typedef iter_impl<T> self_type;
            typedef typename std::conditional<
                std::is_const<T>::value, typename T::const_iterator, typename T::iterator
            >::type it_type;


            virtual ~iter_impl() {}


            iter_impl(container_type& c, bool end = false)
                : it(end ? c.end() : c.begin())
            { }


            bool operator!=(iter_impl_base const& rhs) const
            {
                it_type const& itr = static_cast<self_type const&>(rhs).it;
                return it != itr;
            }


            iter_impl_base& operator++()
            {
                ++it;
                return *this;
            }

            iter_impl_base& operator+(std::size_t i)
            {
                it += i;
                return *this;
            }


            val const& operator*() const
            {
                return deref(std::is_same<typename std::remove_const<T>::type, object>());
            }


            val& operator*()
            {
                return const_cast<val&>(
                    deref(std::is_same<typename std::remove_const<T>::type, object>()));
            }


            val const& deref(std::true_type) const
            {
                return it->second;
            }


            val const& deref(std::false_type) const
            {
                return *it;
            }


            it_type it;
        };



        template<typename T>
        struct iter
        {

            typedef T  value;
            typedef T& reference;
            typedef iter<T> self_type;

            template<typename U>
            struct c_qual
            {
                typedef typename std::conditional<
                    std::is_const<T>::value, U const, U
                >::type type;
            };


            iter(value& v, bool end = false)
                : v(v)
                , end(end)
                , it_impl(v.type() == type_info::object
                    ? static_cast<iter_impl_base*>(new iter_impl<typename c_qual<object>::type>(v.o_, end))
                    : static_cast<iter_impl_base*>(new iter_impl<typename c_qual<array>::type>(v.a_, end)))
            { }


            bool operator==(self_type const& rhs) const
            {
                return !it_impl->operator!=(*(rhs.it_impl));
            }


            bool operator!=(self_type const& rhs) const
            {
                return it_impl->operator!=(*(rhs.it_impl));
            }


            self_type& operator++()
            {
                it_impl->operator++();
                return *this;
            }


            self_type& operator+(std::size_t i)
            {
                it_impl->operator+(i);
                return *this;
            }


            reference operator*() const
            {
                return it_impl->operator*();
            }


            operator iter<typename std::add_const<T>::type> ()
            {
                return iter<value const>(v, end);
            }


            value& v;
            bool end;
            std::shared_ptr<iter_impl_base> it_impl;
        };


    }


    iterator begin(val& v)
    {
       return iterator(v);
    }


    iterator end(val& v)
    {
       return iterator(v, true);
    }


    const_iterator begin(val const& v)
    {
        return const_iterator(v);
    }


    const_iterator end(val const& v)
    {
        return const_iterator(v, true);
    }


} }
