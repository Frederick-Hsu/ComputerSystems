#!/bin/bash
#
# File name     : build.sh
# 

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
gcc -v echo_client.c -o echo_client -L./ -lnet -lrobustio -I./