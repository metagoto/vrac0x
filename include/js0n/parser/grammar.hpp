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
    struct tok : seq</*ws,*/ T, ws> {};

    template<char C>
    struct ch_tok : seq</*ws,*/ ch<char,C>, ws> {};

    struct true_ : seq<ch<char,'t'>, store<ch<char,'r','u','e'>, true_> > {};
    struct false_: seq<ch<char,'f'>, store<ch<char,'a','l','s', 'e'>, false_> > {};
    struct null  : seq<ch<char,'n'>, store<ch<char,'u','l','l'>, null> > {};


    // str
    typedef
    seq<
        ch<char,'\\'>
       ,set<char,'"', '/', '\\', 'b', 'f', 'n', 'r', 't', 'u'>
    > esc_ch;

    struct string :
    seq<
        ch<char,'"'>
       ,store<
            star<
                alter<
                    esc_ch
                   ,any_ch_but<char, '"'> // TODO
                >
            >
           ,string
        >
       ,ch<char,'"'>
    >
    {};


    // num
    typedef range<char,'0','9'> digit;
    typedef range<char,'1','9'> digit19;

    typedef
    seq< set<char,'e', 'E'>, opt<set<char,'+','-'> >
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


    struct integer :
        seq<peek<alter<digit,ch<char,'-'>>>, store< seq<int_, opt<exp> >, integer> >
    {};

    struct decimal :
        seq<peek<alter<digit,ch<char,'-'>>>, store< seq<int_,frac,opt<exp> >, decimal> >
    {};


    // obj
    struct value;

    struct kv_pair :
    seq<
        tok<string>
       ,ch_tok<':'>
       ,value
    > {};

    struct object :
    seq<
        ch_tok<'{'>
       ,store<
            opt<
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
           ,object
        >
       ,ch<char,'}'>
    > {};


    // arr
    struct array :
    seq<
        ch_tok<'['>
       ,store<
            opt<
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
           ,array
        >
       ,ch<char,']'>
    > {};


    // value
    struct value :
    tok<
        alter<
            string
           ,decimal
           ,integer
           ,object
           ,array
           ,true_
           ,false_
           ,null
        >
    > {};


    // json
    struct json :
    seq<
        ws
       ,value
       ,eoi
    > {};



} } }
