#pragma once

#include "testiculs/predicates.hpp"
#include "testiculs/basis.hpp"



#define _T_INFO(t) #t, __FILE__, __LINE__
#define _T_INFO1(t,a) std::forward_as_tuple(a), std::forward_as_tuple(#a), _T_INFO(t)
#define _T_INFO2(t,a,b) std::forward_as_tuple(a, b), std::forward_as_tuple(#a, #b), _T_INFO(t)

#define _C_QUAL2(a,b) std::add_const<decltype(a)>::type&,std::add_const<decltype(b)>::type&


#define CHECK(a) \
    vrac0x::testiculs::check(&vrac0x::testiculs::predicate::test,_T_INFO1(CHECK, a));


#define CHECK_NOT(a) \
    vrac0x::testiculs::check( \
        vrac0x::testiculs::predicate::holder<bool>:: \
            not_<vrac0x::testiculs::predicate::test>() \
       ,_T_INFO1(CHECK_NOT, a));


#define CHECK_EQ(a,b) \
    vrac0x::testiculs::check(&vrac0x::testiculs::predicate::eq<decltype(a),decltype(b)> \
                            ,_T_INFO2(CHECK_EQ, a, b));


#define CHECK_NEQ(a,b) \
    vrac0x::testiculs::check( \
        vrac0x::testiculs::predicate::holder<_C_QUAL2(a,b)>:: \
            not_<vrac0x::testiculs::predicate::eq<_C_QUAL2(a,b)>>() \
       ,_T_INFO2(CHECK_NEQ, a, b));


#define CHECK_STREQ(a,b) \
    vrac0x::testiculs::check(&vrac0x::testiculs::predicate::str_eq \
                            ,_T_INFO2(CHECK_STREQ, a, b));


#define CHECK_STRNEQ(a,b) \
    vrac0x::testiculs::check( \
        vrac0x::testiculs::predicate::holder<char const*,char const*>:: \
            not_<vrac0x::testiculs::predicate::str_eq>() \
       ,_T_INFO2(CHECK_STRNEQ, a, b));


#define ASSERT(a) \
    vrac0x::testiculs::assert(&vrac0x::testiculs::predicate::test,_T_INFO1(ASSERT, a));


#define ASSERT_NOT(a) \
    vrac0x::testiculs::assert( \
        vrac0x::testiculs::predicate::holder<bool>:: \
            not_<vrac0x::testiculs::predicate::test>() \
       ,_T_INFO1(ASSERT_NOT, a));


#define ASSERT_EQ(a,b) \
    vrac0x::testiculs::assert(&vrac0x::testiculs::predicate::eq<decltype(a),decltype(b)> \
                             ,_T_INFO2(ASSERT_EQ, a, b));


#define ASSERT_NEQ(a,b) \
    vrac0x::testiculs::assert( \
        vrac0x::testiculs::predicate::holder<_C_QUAL2(a,b)>:: \
            not_<vrac0x::testiculs::predicate::eq<_C_QUAL2(a,b)>>() \
       ,_T_INFO2(ASSERT_NEQ, a, b));


#define ASSERT_STREQ(a,b) \
    vrac0x::testiculs::assert(&vrac0x::testiculs::predicate::str_eq \
                             ,_T_INFO2(ASSERT_STREQ, a, b));


#define ASSERT_STRNEQ(a,b) \
    vrac0x::testiculs::assert( \
        vrac0x::testiculs::predicate::holder<char const*,char const*>:: \
            not_<vrac0x::testiculs::predicate::str_eq>() \
       ,_T_INFO2(ASSERT_STRNEQ, a, b));
