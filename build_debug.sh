#!/bin/bash

set -e

. $HOME/sh/lib/gcc_util.sh
has_gcc_trunk || { echo "no gcc trunk found. exiting"; exit; }


gcc -Wl,-rpath,$HOME/local-gcc-trunk/lib64 \
    -Wl,-rpath,$HOME/local-gcc-trunk/lib \
    -I $HOME/local-gcc-trunk/include \
    -L $HOME/local-gcc-trunk/lib64 \
    -L $HOME/local-gcc-trunk/lib \
    -lstdc++ -lpthread \
    -std=c++0x -fpic \
    -o $1.out \
    -Wall -Wextra -Werror -pedantic -g -O0 \
    -fno-deduce-init-list \
    $1.cpp \
    $2
