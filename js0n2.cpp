
#include "include/testiculs.hpp"

#include "include/veg/operators.hpp"
#include "include/veg/chars.hpp"
#include "include/veg/context.hpp"
#include "include/veg/store.hpp"
#include "include/veg/ast.hpp"

#include "include/js0n.hpp"
#include "include/js0n/print.hpp"

using namespace vrac0x::veg;
using namespace vrac0x::js0n;

////

typedef set<char,' ','\n','\r','\t'> space;
typedef plus<space> spaces;
typedef star<space> ws;


template<typename T>
struct tok : public seq<ws, T, ws> {};

template<char C>
struct ch_tok : public seq<ws, ch<char,C>, ws> {};


typedef ch<char,'t','r','u','e'>     json_true;
typedef ch<char,'f','a','l','s','e'> json_false;
typedef ch<char,'n','u','l','l'>     json_null;


typedef
seq
< ch<char,'\\'>
, set<char,'"', '/', '\\', 'b', 'f', 'n', 'r', 't', 'u'>
>
esc_ch;


typedef
seq
< ch<char,'"'>
, star
  < alter
    < range<char,'a','z','A','Z','0','9'> // easy
    , ch<char,' '>
    , esc_ch
    >
  >
, ch<char,'"'>
>
json_string;


typedef
plus
< range<char,'0','9'> // easy
>
json_number;


struct json_object;
struct json_array;

struct json_value : public
tok
< alter
  < store<json_string>
  , store<json_number>
  , store<json_object>
  , store<json_array>
  , store<json_true>
  , store<json_false>
  , store<json_null>
  >
> {};


struct json_kv_pair : public
seq
< tok<store<json_string> >
, ch_tok<':'>
, json_value
> {};

struct json_object : public
seq
< ch_tok<'{'>
, opt
  < seq
    < json_kv_pair
    , star
      < seq
        < ch_tok<','>
        , json_kv_pair
        >
      >
    >
  >
, ch<char,'}'>
> {};


struct json_array : public
seq
< ch_tok<'['>
, opt
  < seq
    < json_value
    , star
      < seq
        < ch_tok<','>
        , json_value
        >
      >
    >
  >
, ch<char,']'>
> {};



////

namespace vrac0x { namespace veg {
    template<>
    struct type_to_int<json_string>
    {  static const int value = 1; };

    template<>
    struct type_to_int<json_number>
    {  static const int value = 2; };

    template<>
    struct type_to_int<json_object>
    {  static const int value = 3; };

    template<>
    struct type_to_int<json_array>
    {  static const int value = 4; };

    template<>
    struct type_to_int<json_true>
    {  static const int value = 5; };
    \
    template<>
    struct type_to_int<json_false>
    {  static const int value = 6; };

    template<>
    struct type_to_int<json_null>
    {  static const int value = 7; };
} }


struct json_parser : public ast<std::string>
{

    json_parser(std::string const& s)
        : input(s)
    { }


    val parse()
    {
        tree_context<std::string::const_iterator, json_parser> c(input.begin(), input.end(), *this);

        if (json_value::match(c) && root->children.size())
        {
            //traverse();
            return build((*(root->children.begin())).get());
        }
        return null;
    }

 private:
    val build(ast<std::string>::node_base* n)
    {

        switch (n->type())
        {
            case 1 : {// string
                std::string const& s = n->str();
                return s.substr(1, s.size()-2);
            }
            case 2 : // num
                return stoi(n->str()); // TODO fix
            case 5 :
                return true;
            case 6 :
                return false;
            case 7 :
                return null_type();
            case 3 :  { // obj
                val obj = {};
                std::string key;
                auto i = n->children.begin();
                auto e = n->children.end();
                for ( ; i != e; ++i) {
                    key = (*i)->str();
                    ++i;
                    obj[key] = build(i->get());
                }
                return obj;
            }
            case 4 : { // array
                val arr = empty_array;
                typedef typename val::array array_type;
                array_type& raw_arr = get<array_type>(arr);
                auto i = n->children.begin();
                auto e = n->children.end();
                for ( ; i != e; ++i) {
                    raw_arr.push_back(build(i->get()));
                }
                return arr;
            }
            case 0 : // should not reach
            default :
                break;
        }
        return val();
    }

    std::string input;
};


int main()
{
    val j = json_parser("42").parse();
    PRINT(j);

    j = json_parser(R"("str")").parse();
    PRINT(j);

    j = json_parser(R"(["  blah  ", [], true])").parse();
    PRINT(j);

    j = json_parser(R"([1,2, "str" , { "key" :  "val", "": [true, null] }, false,[]])").parse();
    PRINT(j);

    j = json_parser(R"( { "key" : "v\\al", "": [true, null] } )").parse();
    PRINT(j);

    j = json_parser(R"("")").parse();
    PRINT(j);

    j = json_parser(R"(   false)").parse();
    PRINT(j);

    j = json_parser(R"(error)").parse();
    PRINT(j);

}
