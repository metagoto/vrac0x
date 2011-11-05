
#include "include/js0n.hpp"
#include "include/js0n/print.hpp"
#include "include/testiculs.hpp"

#include "include/js0n/traits/simple64.hpp"
#include "include/js0n/traits/compact.hpp"
#include "include/js0n/traits/large.hpp"
#include "include/js0n/traits/deque.hpp"


int main()
{
    using namespace vrac0x::js0n;
    typedef val::k k;


    val json = {
        "bool"_k  = true,
        "key"_k   = "val",
        "other"_k = "da value",
        "int"_k   = 42,
        "obj"_k   = {
            "key2"_k = null,
            "arr"_k  = {1, 2, "STR", {3, 1.4142}, {"dd"_k = 66}, false}
        },
        "pi"_k    = 3.14
    };


    {
        PRINT(json);
        val j = json;
        PRINT(j);
    }

    {
        typedef val::string string;

        val j = 3;
        CHECK_EQ(j, 3);
        CHECK_EQ(3, j);

        j = 3.14;
        CHECK_NEQ(j, 3);
        CHECK_EQ(j, 3.14);
        CHECK_EQ(3.14, j);

        j = true;
        CHECK_NEQ(j, 3.14);
        CHECK_EQ(j, true);
        CHECK_EQ(true, j);

        j = null;
        CHECK_NEQ(j, true);
        CHECK_EQ(j, null);
        CHECK_EQ(null, j);

        j = "str";
        CHECK_NEQ(j, null);
        CHECK_STREQ(j, "str");
        CHECK_STREQ("str", j);
        CHECK_STRNEQ(j, "strz");
        CHECK_STRNEQ("zstr", j);
        CHECK_EQ(j, string("str"));
        CHECK_EQ(string("str"), j);
        CHECK_NEQ(j, string("strx"));
        CHECK_NEQ(string("strx"), j);

        j = string{"str"};
        CHECK_STREQ( j, "str");
        CHECK_STREQ( "str", j);
        CHECK_STRNEQ(j, "strz");
        CHECK_STRNEQ("zstr", j);
        CHECK_EQ(j, string("str"));
        CHECK_EQ(string("str"), j);
        CHECK_NEQ(j, string("strx"));
        CHECK_NEQ(string("strx"), j);

        j = {1, 2};
        val j2 = {1, 2};
        CHECK_EQ(j, j2);
        CHECK_EQ(j2, j);
        CHECK( j == val({1,2}) );
        CHECK( j != val({1,2,3}) );


        j = {k("a") = 1, k("b") = 2};
        j2= {k("a") = 1, k("b") = 2};
        CHECK_EQ(j, j2);
        CHECK_EQ(j2, j);
        CHECK( j == val({k("a") = 1, k("b") = 2}) );
        CHECK( j != val({k("a") = 1, k("b") = 2, k("c") = 3}) );
    }

    {
        val j = {}; //empty_object;

        j["key"] = 1;
        CHECK_EQ(j["key"], 1);
        CHECK_NEQ(j["key"], 2);

        j["key"] = "blah";
        CHECK_NEQ(  j["key"], 1);
        CHECK_STREQ(j["key"], "blah");

        j["key2"] = {true, "test",null};
        CHECK_EQ(   j["key2"][0], true);
        CHECK_STREQ(j["key2"][1], "test");
        CHECK_EQ(   j["key2"][2], null);

        val j2 = {0,1,2};
        CHECK_EQ(j2[0], 0);
        CHECK_EQ(j2[1], 1);
        CHECK_EQ(j2[2], 2);
        CHECK_ANY_THROW(j2[3]);

        j2[0] = {}; //empty_object;
        CHECK_NO_THROW(j2[0]["key"]);
        CHECK_EQ(j2[0]["key"], null);

    }


    {
        typedef val::iterator iterator;
        typedef val::const_iterator const_iterator;

        val jo = {k("x")=1, k("y")=true, k("z")=null};
        val ja = {1, true, null};
        val const cjo = jo;
        val const cja = ja;

        for (auto v : ja) {
            PRINT(v);
        }

        for (val& v : ja) {
            PRINT(v);
        }

        for (val const& v : ja) {
            PRINT(v);
        }

        const_iterator cit = begin(cja);
        const_iterator cit2 = begin(ja);
        iterator it = begin(ja);
        const_iterator cit3 = it;
        //iterator it2 = begin(cja); // error const -> non const

        {
            const_iterator cit = begin(cjo);
            const_iterator cit2 = begin(jo);
            iterator it = begin(jo);
            const_iterator cit3 = it;
        }

        CHECK_NEQ(begin(ja), end(ja));
        CHECK(begin(ja) != end(ja));
        CHECK_EQ(end(ja), end(ja));
        CHECK(end(ja) == end(ja));

        CHECK_NEQ(begin(jo), end(jo));
        CHECK(begin(jo) != end(jo));
        CHECK_EQ(end(jo), end(jo));
        CHECK(end(jo) == end(jo));

        std::for_each(begin(cjo), end(cjo), [](val const& v){PRINT(v)});
        //std::for_each(begin(cj), end(cj), [](val& v){});
        std::for_each(begin(cjo), end(cjo), [](val v){PRINT(v)});

        int i = 0;
        std::for_each(begin(cjo), end(cjo), [&](val const& v){
            CHECK_EQ(v, ja[i++]);
        });

        for (val& v : ja) {
            v = "str";
        }
        std::for_each(begin(ja), end(ja), [](val const& v){
            CHECK_STREQ(v, "str");
        });
    }

    {
        typedef val::string string;
        typedef val::object object;
        typedef val::array array;
        typedef val::pair pair;

        val j = json;
        val& jj = j;
        val const& cjj = jj;

        string const& cs = get<string>(jj["key"]);
        CHECK_EQ(cs, "val");

        string& s = get<string>(jj["other"]);
        CHECK_EQ(s, "da value");
        s = "new";
        CHECK_STREQ(jj["other"], "new");
        CHECK_EQ(get<string>(jj["other"]), "new");

//        bool const& b = get<bool>(val{k("woot")=true}["woot"]);
//        CHECK_EQ(b, true);

        CHECK_ANY_THROW(get<string>(jj["int"]));

        //string& bl = get<string>(cjj["key"]); // error const -> non const

        string* ps = get<string>(&jj["key"]);
        CHECK_EQ(*ps, "val");

        string const* cps = get<string>(&cjj["key"]);
        CHECK_EQ(*cps, "val");

        string* es = get<string>(&jj["int"]);
        CHECK_EQ(es, nullptr);

        jj["key"] = 3.14;
        CHECK_ANY_THROW(get<string>(cjj["key"]));
        CHECK_NO_THROW(get<double>(cjj["key"]));

        CHECK_NO_THROW(get<bool>(jj["bool"]));
        CHECK_NO_THROW(get<double>(jj["pi"]));
        CHECK_ANY_THROW(get<array>(jj["obj"]));

        object const& o = get<object>(jj["obj"]);
        for (pair const& p : o) {
            PRINT(p.second);
        }

    }

    {
        typedef basic_val<tag::simple64> val64;
        typedef val64::k k;

        val64 j = -1234567890123456789; //45LL;
        PRINT(j);
        CHECK_EQ(j, -1234567890123456789);


        j = 1;
        PRINT(j);
        CHECK_EQ(j, 1);

        j = 2u;
        PRINT(j);
        CHECK_EQ(j, 2u);

        j = 1.3f;
        PRINT(j);
        CHECK_EQ((float)j, 1.3f);

        j = 1.2;
        PRINT(j);
        CHECK_EQ(j, 1.2);

    }

    {
        typedef basic_val<tag::compact> val;

        val j = -1;
        CHECK_EQ(j, (short)-1);
        CHECK_EQ(j, -1);
        CHECK_EQ(j, -1L);
        CHECK_EQ(j, -1LL);

        j = 1.2;
        CHECK_EQ(j, 1.2);
        CHECK_EQ(j, 1.2f);
        CHECK_EQ(j, (double)1.2);
        CHECK_EQ(j, (long double)1.2);

        j = { 1, 1.1f, 1.1, (long double)1.1, (short)2, 2, 2L, 22222222222228LL};
        PRINT(j);

    }


    {
        typedef basic_val<tag::simple> val;

        val j = -1;
        CHECK_EQ(j, (short)-1);
        CHECK_EQ(j, -1);
        CHECK_EQ(j, -1L);
        CHECK_EQ(j, -1LL);

        j = 1.2;
        CHECK_EQ(j, 1.2);
        CHECK_EQ(j, 1.2f);
        CHECK_EQ(j, (double)1.2);
        CHECK_EQ(j, (long double)1.2);

        j = { 1, 1.1f, 1.1, (long double)1.1, (short)2, 2, 2L, 22222222222228LL};
        PRINT(j);

    }

    {
        typedef basic_val<tag::large> val;

        val j = -1;
        CHECK_EQ(j, (short)-1);
        CHECK_EQ(j, -1);
        CHECK_EQ(j, -1L);
        CHECK_EQ(j, -1LL);

        j = 1.2;
        CHECK_EQ(j, 1.2);
        CHECK_EQ(j, 1.2f);
        CHECK_EQ(j, (double)1.2);
        CHECK_EQ(j, (long double)1.2);

        std::cout << sizeof(basic_val<tag::compact>) << std::endl;
        std::cout << sizeof(basic_val<tag::simple>) << std::endl;
        std::cout << sizeof(basic_val<tag::simple64>) << std::endl;
        std::cout << sizeof(basic_val<tag::large>) << std::endl;
        std::cout << sizeof(basic_val<tag::deque>) << std::endl;

        j = { 1, 1.1f, 1.1, (long double)1.1, (short)2, 2, 2L, 22222222222228LL};
        PRINT(j);

    }

    {
        typedef basic_val<tag::deque> val;

        val j = -1;
        CHECK_EQ(j, (short)-1);
        CHECK_EQ(j, -1);
        CHECK_EQ(j, -1L);
        CHECK_EQ(j, -1LL);

        j = 1.2;
        CHECK_EQ(j, 1.2);
        CHECK_EQ(j, 1.2f);
        CHECK_EQ(j, (double)1.2);
        CHECK_EQ(j, (long double)1.2);

        j = { 1, 1.1f, 1.1, (long double)1.1, (short)2, 2, 2L, 22222222222228LL};
        PRINT(j);

        CHECK_EQ((double)1.2f, (double)1.2);
        std::cout << ((double)1.2f == (double)1.2) << std::endl;
        std::cout << (double)1.2f << " " << (double)1.2 << std::endl;

    }


}
