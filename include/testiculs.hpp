#pragma once

#include "testiculs/predicates.hpp"
#include "testiculs/basis.hpp"


#define _T_INFO(t) #t, __FILE__, __LINE__
#define _T_INFO1(t,a) std::forward_as_tuple(a), std::forward_as_tuple(#a), _T_INFO(t)
#define _T_INFO2(t,a,b) std::forward_as_tuple(a, b), std::forward_as_tuple(#a, #b), _T_INFO(t)

#define _C_QUAL2(a,b) std::add_const<decltype(a)>::type&,std::add_const<decltype(b)>::type&
#define _ASSERT(a) vrac0x::testiculs::assert_(a)


#define _CHECK(t,a) \
    vrac0x::testiculs::check(&vrac0x::testiculs::predicate::test,_T_INFO1(t,a))

#define CHECK(a) _CHECK(CHECK, a);
#define ASSERT(a) _ASSERT(_CHECK(ASSERT,a));


#define _CHECK_NOT(t,a) \
    vrac0x::testiculs::check( \
        vrac0x::testiculs::predicate::holder<bool>:: \
            not_<vrac0x::testiculs::predicate::test>() \
       ,_T_INFO1(t,a))

#define CHECK_NOT(a) _CHECK_NOT(CHECK_NOT,a);
#define ASSERT_NOT(a) _ASSERT(_CHECK_NOT(ASSERT_NOT,a));


#define _CHECK_EQ(t,a,b) \
    vrac0x::testiculs::check(&vrac0x::testiculs::predicate::eq<decltype(a),decltype(b)> \
                            ,_T_INFO2(t,a,b))

#define CHECK_EQ(a,b) _CHECK_EQ(CHECK_EQ,a,b);
#define ASSERT_EQ(a,b) _ASSERT(_CHECK_EQ(ASSERT_EQ,a,b));


#define _CHECK_NEQ(t,a,b) \
    vrac0x::testiculs::check( \
        vrac0x::testiculs::predicate::holder<_C_QUAL2(a,b)>:: \
            not_<vrac0x::testiculs::predicate::eq<_C_QUAL2(a,b)>>() \
       ,_T_INFO2(t,a,b))

#define CHECK_NEQ(a,b) _CHECK_NEQ(CHECK_NEQ,a,b);
#define ASSERT_NEQ(a,b) _ASSERT(_CHECK_NEQ(ASSERT_NEQ,a,b));


#define _CHECK_STREQ(t,a,b) \
    vrac0x::testiculs::check(&vrac0x::testiculs::predicate::str_eq \
                            ,_T_INFO2(t,a,b))

#define CHECK_STREQ(a,b) _CHECK_STREQ(CHECK_STREQ,a,b);
#define ASSERT_STREQ(a,b) _ASSERT(_CHECK_STREQ(ASSERT_STREQ,a,b));


#define _CHECK_STRNEQ(t,a,b) \
    vrac0x::testiculs::check( \
        vrac0x::testiculs::predicate::holder<char const*,char const*>:: \
            not_<vrac0x::testiculs::predicate::str_eq>() \
       ,_T_INFO2(t,a,b))

#define CHECK_STRNEQ(a,b) _CHECK_STRNEQ(CHECK_STRNEQ,a,b);
#define ASSERT_STRNEQ(a,b) _ASSERT(_CHECK_STRNEQ(ASSERT_STRNEQ,a,b));
