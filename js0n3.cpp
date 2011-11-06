
#include "include/js0n.hpp"
#include "include/js0n/parser.hpp"
#include "include/js0n/print.hpp"
#include "include/testiculs.hpp"


vrac0x::js0n::val operator"" _json(char const* s, std::size_t n)
{
    vrac0x::js0n::parser<char const*> p;
    return p.parse<vrac0x::js0n::val>(s, s+n);
}


int main()
{
    using namespace vrac0x::js0n;


    auto j = R"(
    {
        "日本語" : "ok",
        "more" : ["こちらは田中さんです", 3, "教えてもらった"]
    }
    )"_json;

    static_assert(std::is_same<decltype(j), val>::value
                 ,"something went horribly wrong");


    val j2 =
    {
        "日本語"_k = "ok",
        "more"_k = {"こちらは田中さんです", 3, "教えてもらった"}
    };


    CHECK_EQ(j, j2);

}
