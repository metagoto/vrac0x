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
        struct tstack;

        typedef Iterator                         iterator_type;
        typedef std::vector<item>                container_type;
        typedef std::stack<item, container_type> stack_type;


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


        struct tstack : stack_type
        {
            typedef stack_type base_type;

            std::size_t finalize(iterator_type e, std::size_t index)
            {
                item& i = this->c[index];
                i.end_ = e;
                i.delta_ = this->size() - index - 1;
                return i.parent_;
            }

            std::size_t push(item&& i)
            {
                base_type::emplace(std::move(i));
                return this->size() - 1;
            }


            typename base_type::container_type& container()
            {
                return this->c;
            }

//            void traverse()
//            {
//                for (std::size_t i = 0; i < this->c.size(); ++i)
//                {
//                    item& si = this->c[i];
//                    std::cout << i << " t: " << si.type << " d: " << si.delta << std::endl;
//                }
//            }
        };



        void finalize_node(iterator_type e)
        {
            c_ = s_.finalize(e, c_);
        }

        void forget_node()
        {
            item const& i = s_.top();
            c_ = i.parent_;
            s_.pop();
        }

        template<typename T>
        void create_node(iterator_type s)
        {
            c_ = s_.push(item(type_to_int<T>::value, s, c_));
        }


        typename tstack::container_type& container()
        {
           return s_.container();
        }


//        void traverse()
//        {
//            s_.traverse();
//        }


    private:
        tstack      s_;
        std::size_t c_;

    };


} } //ns
