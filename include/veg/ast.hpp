#pragma once

#include <algorithm>
#include <functional>
#include <list>

#include <memory>

namespace vrac0x { namespace veg {


template<typename T>
struct type_to_int
{
    static const int value = 0;
};

template<typename String>
struct ast
{

    typedef String string_type;
    typedef typename String::const_iterator iterator_type; ///////////////


    struct node_base
    {

        node_base(node_base const&) = delete;
        node_base& operator=(node_base const&) = delete;

        node_base()
            : parent(0)
        {}

        node_base(iterator_type s)
            : parent(0)
            , start(s)
        {
        }


        virtual ~node_base()
        {
//            std::for_each(children.begin(), children.end(), [](node_base* n){
//                delete n;
//                n = nullptr;
//            });
        }


        void add_child(node_base* child)
        {
            children.push_back(std::unique_ptr<node_base>(child));
            child->parent = this;
        }


        void remove_child(node_base* child)
        {
            auto it = std::find_if(children.begin(), children.end()
                                  ,[child](std::unique_ptr<node_base>& p){
                return p.get() == child;
            });
            if (it != children.end())
                children.erase(it);
        }


        void traverse(int depth = 0) const
        {
            auto i = children.begin();
            auto e = children.end();
            for ( ; i != e; ++i) {
                //debug
                std::cout << depth << "; " << (*i)->str() << " TYPE: " << (*i)->type() << std::endl;
                (*i)->traverse(depth+1);
            }
        }


        string_type str() const
        {
            return string_type(start, end);
        }


        virtual int type()
        {
            return 0;
        }

        node_base* parent;
        iterator_type start;
        iterator_type end;
        std::list<std::unique_ptr<node_base>> children;

    };


    template<typename T>
    struct node : public node_base
    {
        node(iterator_type s)
            : node_base(s)
        {
        }

        virtual int type()
        {
            return type_to_int<T>::value;
        }

    };




    void finalize_node(iterator_type e)
    {
        current->end = e;
        current = current->parent;
    }

    void forget_node()
    {
        node_base* old = current;
        current = current->parent;
        current->remove_child(old);
    }

    template<typename T>
    void create_node(iterator_type s)
    {
        node_base* n = new node<T>(s);
        current->add_child(n);
        current = n;
    }


    ast()
        : root(new node_base())
        , current(root)
    {
    }

    ~ast()
    {
        delete root;
        root = nullptr;
    }

    void traverse()
    {
        root->traverse();
    }

    node_base* root;
    node_base* current;

};


} } //ns
