#pragma once

#include <memory>


namespace vrac0x { namespace js0n
{

    inline namespace detail
    {


        struct iter_impl_base
        {
            virtual ~iter_impl_base() {}
            virtual bool operator!=(iter_impl_base const& rhs) const = 0;
            virtual iter_impl_base& operator++() = 0;
            virtual iter_impl_base& operator+(std::size_t i) = 0;
            virtual val const& operator*() const = 0;
            virtual val& operator*() = 0;
        };


        template<typename T>
        struct iter_impl : public iter_impl_base
        {

            typedef iter_impl<T> self_type;
            typedef T container_type;
            typedef typename T::const_iterator it_type;

            virtual ~iter_impl() {}


            iter_impl(container_type const& c, bool end = false)
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
                return deref(std::is_same<T, object>());
            }


            val& operator*()
            {
                return const_cast<val&>(deref(std::is_same<T, object>()));
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

    }



    struct iterator
    {

        iterator(val const& v, bool end = false)
            : it_impl(v.type() == type_info::object
                      ? static_cast<iter_impl_base*>(new iter_impl<object>(v.o_, end))
                      : static_cast<iter_impl_base*>(new iter_impl<array>(v.a_, end)))
        { }


        iterator(val& v, bool end = false)
            : it_impl(v.type() == type_info::object
                      ? static_cast<iter_impl_base*>(new iter_impl<object>(v.o_, end))
                      : static_cast<iter_impl_base*>(new iter_impl<array>(v.a_, end)))
        { }


        bool operator!=(iterator const& rhs) const
        {
            return it_impl->operator!=(*(rhs.it_impl));
        }


        iterator& operator++()
        {
            it_impl->operator++();
            return *this;
        }


        iterator& operator+(std::size_t i)
        {
            it_impl->operator+(i);
            return *this;
        }


        val const& operator*() const
        {
            return it_impl->operator*();
        }


        val& operator*()
        {
            return it_impl->operator*();
        }


        std::shared_ptr<iter_impl_base> it_impl;
    };


    // TODO const_iterator

    iterator begin(val const& v)
    {
        return iterator(v);
    }


    iterator end(val const& v)
    {
        return iterator(v, true);
    }


    iterator begin(val& v)
    {
       return iterator(v);
    }


    iterator end(val& v)
    {
       return iterator(v, true);
    }


} }
