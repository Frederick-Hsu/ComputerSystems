#!/bin/sh

# File name     : build.sh
# Description   : How to build your program.
#


gcc -m32 -o test_32bit.o test_32_or_64_bit.c
./test_32bit.o



gcc -m64 -o test_64bit.o test_32_or_64_bit.c
./test_64bit.o


gcc -o test_default.o test_32_or_64_bit.c
./test_default.o

gcc -shared -fPIC csapp.c -o libcsapp.so -lpthread
