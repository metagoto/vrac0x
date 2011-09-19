#include <iostream>

#include "include/js0n.hpp"
#include "include/js0n/print.hpp"

#include "include/testiculs.hpp"


int main()
{
    using vrac0x::js0n::val;
    using vrac0x::js0n::k;
    using vrac0x::js0n::null;


    // when the compiler supports user defined literals
    // we should be able to "coolify" the object's keys notation
    // with something like: "key"k = value
    // for now, k("key") = value

    val json = {
        k("bool")  = true,
        k("key")   = "val",
        k("other") = "da value",
        k("int")   = 42,
        k("obj")   = {
            k("key2") = null,
            k("arr")  = {1, 2, "STR", {3, 1.4142}, {k("dd") = 66}, false}
        },
        k("pi")    = 3.14
    };


    {
        PRINT(json);
        val j = json;
        PRINT(j);
    }

    {
        using vrac0x::js0n::string; // std::string btw

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
        using vrac0x::js0n::empty_array;
        using vrac0x::js0n::empty_object;

        val j = empty_object;

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

        j2[0] = empty_object;
        CHECK_NO_THROW(j2[0]["key"]);
        CHECK_EQ(j2[0]["key"], null);

    }


    {
        using vrac0x::js0n::begin;
        using vrac0x::js0n::end;
        using vrac0x::js0n::iterator;
        using vrac0x::js0n::const_iterator;

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
        using vrac0x::js0n::get;
        using vrac0x::js0n::string;
        using vrac0x::js0n::object;
        using vrac0x::js0n::array;
        using vrac0x::js0n::pair;

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

        bool const& b = get<bool>(val{k("woot")=true}["woot"]);
        CHECK_EQ(b, true);

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

}
