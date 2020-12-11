#!/bin/bash
#
# File name     : build.sh
# 

rm -frv echo_client.o
rm -frv *.so*
rm -frv *.a

cd ../
cd libnet/
make rebuild
make install

cd ../
cd librobustio/
make rebuild
make install 

cd ../client/
gcc -rdynamic echo_client.c -o echo_client.o -ldl

# ./echo_client.o 127.0.0.1 2058
