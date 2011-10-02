#pragma once

#include "../../veg/context.hpp"
#include "../../veg/ast.hpp"


namespace vrac0x { namespace veg
{
    template<> struct type_to_int<js0n::grammar::string>
    {  static const int value = 1; };

    template<> struct type_to_int<js0n::grammar::number>
    {  static const int value = 2; };

    template<> struct type_to_int<js0n::grammar::object>
    {  static const int value = 3; };

    template<> struct type_to_int<js0n::grammar::array>
    {  static const int value = 4; };

    template<> struct type_to_int<js0n::grammar::true_>
    {  static const int value = 5; };

    template<> struct type_to_int<js0n::grammar::false_>
    {  static const int value = 6; };

    template<> struct type_to_int<js0n::grammar::null>
    {  static const int value = 7; };
} }


// TODO: refactor
namespace vrac0x { namespace js0n
{

    inline namespace detail
    {

        template<typename It>
        struct parser : public vrac0x::veg::ast<It>
        {

            typedef It iterator_type;
            typedef typename vrac0x::veg::ast<iterator_type>::range_type range_type;
            typedef typename std::iterator_traits<iterator_type>::value_type char_type;
            typedef std::basic_string<char_type> string_type;
            typedef typename vrac0x::veg::ast<iterator_type>::node_base node_type;


            parser(iterator_type beg, iterator_type end)
                : begin(beg)
                , end(end)
            { }


            template<typename T>
            T parse()
            {
                vrac0x::veg::tree_context<
                    iterator_type, parser
                > ctx(begin, end, *this);

                if (grammar::json::match(ctx) && this->root()->children.size())
                {
                    //traverse();
                    return build<T>((*(this->root()->children.begin())).get());
                }
                return null;
            }


         private:
            template<typename T>
            T build(node_type* n)
            {

                switch (n->type())
                {
                    case 1 : { // string
                        range_type const& r = n->range();
                        return string_type{r.first, r.second}
                            .substr(1, std::distance(r.first, r.second)-2);
                    }
                    case 2 : { // num
                        range_type const& r = n->range();
                        string_type s{r.first, r.second};
                        if (s.find_first_of('.') != string_type::npos)
                            return std::stod(s); // TODO: does not have unicode str overloads
                        return std::stoi(s);
                    }
                    case 5 :
                        return true;
                    case 6 :
                        return false;
                    case 7 :
                        return null_type();
                    case 3 :  { // obj
                        T obj = {};
                        string_type key;
                        auto i = n->children.begin();
                        auto e = n->children.end();
                        for ( ; i != e; ++i) {
                            range_type const& r = (*i)->range();
                            key = string_type{r.first, r.second}
                                    .substr(1, std::distance(r.first, r.second)-2); /// TODO
                            ++i;
                            obj[key] = build<T>(i->get());
                        }
                        return obj;
                    }
                    case 4 : { // array
                        T arr = empty_array;
                        typedef typename T::array array_type;
                        array_type& raw_arr = get<array_type>(arr);
                        auto i = n->children.begin();
                        auto e = n->children.end();
                        for ( ; i != e; ++i) {
                            raw_arr.push_back(build<T>(i->get()));
                        }
                        return arr;
                    }
                    case 0 : // should not reach
                    default :
                        break;
                }
                return T();
            }

            iterator_type begin;
            iterator_type end;
        };

    }


    template<typename T, typename Str>
    T parse(Str const& s)
    {
        typedef typename Str::const_iterator it_type;
        return parser<it_type>(s.cbegin(), s.cend()).parse<T>();
    }

    template<typename T, typename Char, std::size_t N>
    T parse(Char const (&s)[N])
    {
        return parser<Char const*>(s, s+N-1).parse<T>();
    }


    template<typename T, typename It>
    T parse(It beg, It end)
    {
        return parser<It>(beg, end).parse<T>();
    }



} }
