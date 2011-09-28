#pragma once

//tmp
#include <iostream>

namespace vrac0x { namespace veg {


template<typename Iterator>
struct context
{

    typedef Iterator iterator_type;
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    context(iterator_type beg, iterator_type end)
        : beg(beg)
        , end(end)
        , it(beg)
    {
    }


    iterator_type pos()
    {
        return it;
    }

    void pos(iterator_type i)
    {
        it = i;
    }

    value_type operator*()
    {
        return *it;
    }

    void operator++()
    {
        ++it;
    }

    value_type operator++(int i)
    {
        return it++;
    }

    bool eoi()
    {
        return it == end;
    }



    iterator_type beg;
    iterator_type end;
    iterator_type it;

};


template<typename Iterator, typename Tree>
struct tree_context : public context<Iterator>
{
    tree_context(Iterator beg, Iterator end, Tree& tree)
        : context<Iterator>(beg, end)
        , outer_tree(tree)
    {
    }

    Tree& tree()
    {
        return outer_tree;
    }

    Tree& outer_tree;
};



} } //ns
