#include <iostream>

#include "include/js0n.hpp"
#include "include/js0n/print.hpp"

#include "include/testiculs.hpp"


int main()
{
    using vrac0x::js0n::val;
    using vrac0x::js0n::k;
    using vrac0x::js0n::null;
    using vrac0x::js0n::empty_array;
    using vrac0x::js0n::empty_object;
    using vrac0x::js0n::get;


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
        CHECK_EQ(j, std::string("str"));
        CHECK_EQ(std::string("str"), j);
        CHECK_NEQ(j, std::string("strx"));
        CHECK_NEQ(std::string("strx"), j);

        j = std::string{"str"};
        CHECK_STREQ( j, "str");
        CHECK_STREQ( "str", j);
        CHECK_STRNEQ(j, "strz");
        CHECK_STRNEQ("zstr", j);
        CHECK_EQ(j, std::string("str"));
        CHECK_EQ(std::string("str"), j);
        CHECK_NEQ(j, std::string("strx"));
        CHECK_NEQ(std::string("strx"), j);

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

}
