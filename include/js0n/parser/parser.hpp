#pragma once

#include "../../veg/context.hpp"
#include "../../veg/ast_stack.hpp"


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
        struct parser : public vrac0x::veg::ast_stack<It>
        {

            typedef It iterator_type;
            typedef vrac0x::veg::ast_stack<It> base_type;
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

                if (grammar::json::match(ctx) && !this->container().empty())
                {
                    std::size_t start = 0;
                    return build<T>(start);
                }
                return null;
            }


         private:

            template<typename T>
            T build(std::size_t& start)
            {
               typename base_type::item const& si = this->container()[start++];

               switch ((kind)si.type())
               {
                   case kind::string :
                       return string_type{std::next(si.begin()), std::prev(si.end())};
                   case kind::integer :
                       return std::stoi(string_type{si.begin(), si.end()});
                   case kind::decimal :
                       return std::stod(string_type{si.begin(), si.end()});
                   case kind::true_ :
                       return true;
                   case kind::false_ :
                       return false;
                   case kind::object :
                   {
                       T o = {};
                       //auto& ro = get<typename T::object>(o);
                       //ro.reserve(5);
                       std::size_t e = start+si.delta();
                       for ( ; start != e;)
                       {
                           typename base_type::item const& ssi = this->container()[start++];
                           o[string_type{std::next(ssi.begin()), std::prev(ssi.end())}]
                               = build<T>(start);
                       }
                       return o;
                   }
                   case kind::array :
                   {
                       T a = empty_array;
                       auto& ra = get<typename T::array>(a);
                       //ra.reserve(5);
                       std::size_t e = start+si.delta();
                       for ( ; start != e;)
                           ra.push_back(build<T>(start));
                       return a;
                   }
                   default :
                      break;
              }

              return null_type();
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
