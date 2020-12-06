#!/bin/sh

# File name     : build.sh
# Description   : How to build your program.
#


gcc -m32 -o test_32bit test_32_or_64_bit.c
./test_32bit



gcc -m64 -o test_64bit test_32_or_64_bit.c
./test_64bit


gcc -o test_default test_32_or_64_bit.c
./test_default

gcc -shared -fPIC csapp.c -o libcsapp.so -lpthread