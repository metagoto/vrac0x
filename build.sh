#!/bin/bash

set -e

. $HOME/sh/lib/gcc_util.sh
has_gcc_trunk || { echo "no gcc trunk found. exiting"; exit; }


gcc -Wl,-rpath,$HOME/local-gcc-trunk/lib64 \
    -Wl,-rpath,$HOME/local-gcc-trunk/lib \
    -I $HOME/local-gcc-trunk/include \
    -L $HOME/local-gcc-trunk/lib64 \
    -L $HOME/local-gcc-trunk/lib \
    -lstdc++ \
    -Wall -fpic -O3 -s \
    -std=c++0x \
    -o $1.out \
    $1.cpp


