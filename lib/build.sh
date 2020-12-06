#!/bin/sh

# File name     : build.sh
# Description   : How to build the source code files under the project folder.
#

gcc -c addvec.c mulvec.c
ar rcs libvector.a addvec.o mulvec.o

gcc -O2 -c main.c
gcc -static -o calc main.o ./libvector.a
./calc


gcc -shared -fPIC -o libvector.so addvec.c mulvec.c
gcc -o shared_calc main.c ./libvector.so
# gcc -o dynamic_calc main.c -libvector
./shared_calc

gcc -rdynamic -O2 -o dycalc dll.c -ldl
./dycalc