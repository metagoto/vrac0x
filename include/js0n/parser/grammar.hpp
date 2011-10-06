#pragma once

#include "../../veg/operators.hpp"
#include "../../veg/chars.hpp"
#include "../../veg/store.hpp"


namespace vrac0x { namespace js0n { namespace grammar
{

    using namespace vrac0x::veg;


    typedef set<char,' ','\n','\r','\t'> space;
    typedef plus<space> spaces;
    typedef star<space> ws;

    template<typename T>
    struct tok : seq<ws, T, ws> {};

    template<char C>
    struct ch_tok : seq<ws, ch<char,C>, ws> {};

    typedef ch<char,'t','r','u','e'>     true_;
    typedef ch<char,'f','a','l','s','e'> false_;
    typedef ch<char,'n','u','l','l'>     null;


    // str
    typedef
    seq<
        ch<char,'\\'>
       ,set<char,'"', '/', '\\', 'b', 'f', 'n', 'r', 't', 'u'>
    > esc_ch;

    typedef
    seq<
        ch<char,'"'>
       ,star<
            alter<
                range<char,'a','z','A','Z','0','9'> // TODO broader range
               ,ch<char,' '>
               ,esc_ch
               ,any_ch_but<char, '"'> // TODO
            >
        >
       ,ch<char,'"'>
    > string;


    // num
    typedef range<char,'0','9'> digit;
    typedef range<char,'1','9'> digit19;

    typedef
    alter<
        seq<ch<char,'e'>, opt<set<char,'+','-'>>>
       ,seq<ch<char,'E'>, opt<set<char,'+','-'>>>
    > e;

    struct digits :
    seq<
       digit
      ,opt<digits>
    > {};

    typedef
    seq<
        e
       ,digits
    > exp;

    typedef
    seq<
        ch<char,'.'>
       ,digits
    > frac;

    struct int_ :
    alter<
         seq<digit19, opt<digits>>
        ,digit
        ,seq<ch<char,'-'>, digit19, opt<digits>>
        ,seq<ch<char,'-'>, digit>
    > {};

    struct number :
    seq<
         int_
        ,seq<opt<frac>, opt<exp>>
        ,opt<exp>
    > {};

    typedef seq<int_> integer;

    typedef seq<int_, frac, opt<exp> > decimal;


    // obj
    struct value;

    struct kv_pair :
    seq<
        tok<store<string>>
       ,ch_tok<':'>
       ,value
    > {};

    struct object :
    seq<
        ch_tok<'{'>
       ,opt<
            seq<
                kv_pair
               ,star<
                    seq<
                        ch_tok<','>
                       ,kv_pair
                    >
                >
            >
        >
       ,ch<char,'}'>
    > {};


    // arr
    struct array :
    seq<
        ch_tok<'['>
       ,opt<
            seq<
                value
               ,star<
                    seq<
                        ch_tok<','>
                      ,value
                    >
                >
            >
        >
       ,ch<char,']'>
    > {};


    // value
    struct value :
    tok<
        alter<
            store<string>
           //,store<number>
           ,store<decimal>
           ,store<integer>
           ,store<object>
           ,store<array>
           ,store<true_>
           ,store<false_>
           ,store<null>
        >
    > {};


    // json
    struct json :
    seq<
        value
       ,eoi
    > {};



} } }
