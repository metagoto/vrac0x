
#include "include/js0n.hpp"
#include "include/js0n/parser.hpp"
#include "include/js0n/print.hpp"
#include "include/testiculs.hpp"


#define b parse<val> // lame shortcut, i know


int main()
{
    typedef vrac0x::js0n::val val;
    using vrac0x::js0n::parse;
    using vrac0x::js0n::null;

    {
        val j = b("42");
        PRINT(j);

        j = b(R"("str")");
        PRINT(j);

        j = b(std::string("[]"));
        PRINT(j);

        j = b("[ 2 ]");
        PRINT(j);

        j = b("{}");
        PRINT(j);

        j = b(R"({"a":"1"})");
        PRINT(j);

        j = b(R"(["  blah  ", [], true])");
        PRINT(j);

        j = b(R"(
            [
              1, 2.66, "str",
              {
                "key" :  "val",
                ""    : [true, null]
              }, false, [], {}
            ]
        )");
        PRINT(j);

        j = b(R"(
            {
               "key":"v\\al"
              ,"": [true, null]}
        )");
        PRINT(j);

        j = b(std::string("{\"key\":\"val\",\"\":[true,null]}"));
        PRINT(j);

        j = b(R"("")");
        PRINT(j);

        j = b(std::string("   false"));
        PRINT(j);

        char const* s = "false";
        j = b(s, s+5);
        PRINT(j);

        j = b(R"(error)");
        PRINT(j);

        j = b("");
        PRINT(j);

        j = b(u8R"(
            { "日本語" : "ok",
              "00" : [ "こちらは田中さんです", 3, "教えてもらった" ] }
        )");
        PRINT(j);
    }

    {
        val j = b(std::string("0"));
        CHECK_EQ(j, 0);

        j = b("-0");
        CHECK_EQ(j, 0);

        j = b("42");
        CHECK_EQ(j, 42);

        j = b("-42");
        CHECK_EQ(j, -42);

        j = b("0.1");
        CHECK_EQ(j, 0.1);

        j = b("0.1e+2");
        CHECK_EQ(j, 10.);

        j = b("0.1E+2");
        CHECK_EQ(j, 10.);

        j = b("0.1e-2");
        CHECK_EQ(j, 0.001);

        j = b("0.1E-2");
        CHECK_EQ(j, 0.001);

        j = b("-0.1E-2");
        CHECK_EQ(j, -0.001);

        j = b(" 3.14\n");
        CHECK_EQ(j, 3.14);

        j = b(" 3.14e+2\r");
        CHECK_EQ(j, 314.);

        j = b(" 3.14e+2\t");
        CHECK_EQ(j, 314.);

        j = b("\n3.14e-2 ");
        CHECK_EQ(j, 0.0314);

        j = b("\r3.14E-2 ");
        CHECK_EQ(j, 0.0314);

        j = b("\t-3.14e-2 ");
        CHECK_EQ(j, -0.0314);

        j = b("00");
        CHECK_EQ(j, null);
    }

    {
        typedef vrac0x::js0n::basic_val<
            vrac0x::js0n::tag::u32string
           ,vrac0x::js0n::tag::deque
        > val32;

        //val32 j = parse<val32>(U"true"); // TODO std::stod etc
        //CHECK_EQ(j, true);

    }

}
