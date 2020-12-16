#!/usr/bin/env bash
#
# File name     : build.sh
# 

pwd

make clean

cd ../libnet/
make rebuild
make install

cd ../librobustio/
make rebuild
make install

cd ../TINY_Web_Server/
make