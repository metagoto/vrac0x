#include <iostream>

#include "include/js0n.hpp"
#include "include/js0n/print.hpp"


int main()
{
    using vrac0x::js0n::val;
    using vrac0x::js0n::k;

    // when the compiler supports user defined literals
    // we should be able to "coolify" the object's keys notation
    // with something like: "key"k = value
    // for now, k("key") = value


    val j = {
        k("bool") = "true",
        k("key") = "val",
        k("other") = "da value",
        k("intkey") = 42,
        k("suboject") = {
            k("key2") = "val2",
            k("arrkey") = {
                1,
                2,
                "STR",
                { 7, 8, 1.4142 },
                { k("dd") = 66 },
                false
            }
        },
        k("pi") = 3.14

        ,k("MORE") = {
            k("bool") = "true",
            k("key") = "val",
            k("other") = "da value",
            k("intkey") = 42,
            k("suboject") = {
                k("key2") = "val2",
                k("arrkey") = {
                    1,
                    2,
                    "STR",
                    { 7, 8, 1.4142 },
                    { k("dd") = 66 },
                    false
                }
            },
            k("pi") = 3.14
        }
    };


    val j2 = j;

    j = "str";
    j = false;

    val j3 = j2;

    val j4;

    print(j);
    print(j2);
    print(j3);
    print(j4);

}
