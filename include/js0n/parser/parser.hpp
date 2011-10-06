#pragma once

#include "../../veg/context.hpp"
#include "../../veg/ast.hpp"


namespace vrac0x { namespace veg
{
    template<> struct type_to_int<js0n::grammar::string>
    {  static constexpr int value = 1; };

    template<> struct type_to_int<js0n::grammar::integer>
    {  static constexpr int value = 2; };

    template<> struct type_to_int<js0n::grammar::decimal>
    {  static constexpr int value = 3; };

    template<> struct type_to_int<js0n::grammar::object>
    {  static constexpr int value = 4; };

    template<> struct type_to_int<js0n::grammar::array>
    {  static constexpr int value = 5; };

    template<> struct type_to_int<js0n::grammar::true_>
    {  static constexpr int value = 6; };

    template<> struct type_to_int<js0n::grammar::false_>
    {  static constexpr int value = 7; };

    template<> struct type_to_int<js0n::grammar::null>
    {  static constexpr int value = 8; };
} }


// TODO: refactor
namespace vrac0x { namespace js0n
{

    inline namespace detail
    {

        enum class kind : int
        {
            string = 1,
            integer,
            decimal,
            object,
            array,
            true_,
            false_,
            null
        };


        template<typename It>
        struct parser : public vrac0x::veg::ast<It>
        {

            typedef It iterator_type;
            typedef typename vrac0x::veg::ast<iterator_type>::node_base node_type;
            typedef typename vrac0x::veg::ast<iterator_type>::range_type range_type;
            typedef typename std::iterator_traits<iterator_type>::value_type char_type;
            typedef std::basic_string<char_type> string_type;

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
            T build(node_type const* n)
            {

                switch ((kind)n->type())
                {
                    case kind::string :
                    {
                        range_type const& r = n->range();
                        return string_type{std::next(r.first), std::prev(r.second)};
                    }
                    case kind::integer :
                    {
                        range_type const& r = n->range();
                        return std::stoi(string_type{r.first, r.second});
                    }
                    case kind::decimal :
                    {
                        range_type const& r = n->range();
                        return std::stod(string_type{r.first, r.second});
                    }
                    case kind::true_ :
                        return true;
                    case kind::false_ :
                        return false;
                    case kind::null :
                        return null_type();
                    case kind::object :
                    {
                        T o = {};
                        for (auto i(n->children.cbegin()), e(n->children.cend())
                            ;i != e; ++i)
                        {
                            range_type const& r = (*i)->range();
                            o[string_type{std::next(r.first), std::prev(r.second)}]
                                = build<T>((++i)->get());
                        }
                        return o;
                    }
                    case kind::array :
                    {
                        T a = empty_array;
                        auto& ra = get<typename T::array>(a);
                        ra.reserve(n->children.size());
                        for (auto i(n->children.cbegin()), e(n->children.cend())
                            ;i != e; ++i)
                        {
                            ra.push_back(build<T>(i->get()));
                        }
                        return a;
                    }
                    default :
                        break;
                }

                return null_type(); ///TODO
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
