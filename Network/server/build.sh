#!/bin/bash
#
# File name     : build.sh
# Description   : This script builds the code files under server/ directory.
#
#

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
gcc -v echo_server.c -o echo_server -L./ -lnet -lrobustio -I./