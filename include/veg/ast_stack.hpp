#pragma once

#include <vector>
#include <stack>


//// TODO refactor
namespace vrac0x { namespace veg
{


    template<typename T>
    struct type_to_int
    {
        static constexpr int value = 0;
    };


    template<typename Iterator>
    struct ast_stack
    {

        struct item;

        typedef Iterator                         iterator_type;
        typedef std::vector<item>                container_type;


        struct item
        {
            item(int type, iterator_type s, std::size_t parent)
                : type_(type)
                , begin_(s)
                , end_(s)
                , parent_(parent)
                , delta_(0)
            { }

            item() = delete;
            item(item const&) = default;
            item(item&&) = default;
            item& operator=(item const&) = default;
            item& operator=(item&&) = default;

            int type() const { return type_; }
            iterator_type begin() const { return begin_; }
            iterator_type end() const { return end_; }
            std::size_t delta() const { return delta_; }


        private:

            int           type_;
            iterator_type begin_;
            iterator_type end_;
            std::size_t   parent_;
            std::size_t   delta_;

            friend class tsack;
            friend class ast_stack;
        };


        void finalize_node(iterator_type e)
        {
            item& i = s_[c_];
            i.end_ = e;
            i.delta_ = s_.size() - c_ - 1;
            c_ = i.parent_;
        }

        void forget_node()
        {
            item const& i = s_.back();
            c_ = i.parent_;
            s_.pop_back();
        }

        template<typename T>
        void create_node(iterator_type s)
        {
            s_.push_back(item(type_to_int<T>::value, s, c_));
            c_ = s_.size() - 1;
        }


        container_type& container()
        {
           return s_;
        }


//        void traverse()
//        {
//            s_.traverse();
//        }


        void reset()
        {
            s_.clear();
        }

//        ast_stack()
//        {
//            s_.reserve(5);
//        }


    private:
        container_type s_;
        std::size_t    c_;

    };

} } //ns
