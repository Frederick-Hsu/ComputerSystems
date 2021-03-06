#!/bin/bash
#
# File name     : build.sh
# Description   : This script builds the code files under server/ directory.
#
#

rm -frv echo_server.o
rm -frv *.so*
rm -frv *.a

cd ../
cd libnet/
make rebuild
make install

cd ../librobustio/
make rebuild
make install

cd ../server/
gcc -rdynamic echo_server.c -o echo_server.o -ldl

# ./echo_server.o 2058
