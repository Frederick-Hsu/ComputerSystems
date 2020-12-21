#!/bin/bash
#
# File name     : build.sh
# Description   : This shell script is used to build code files under the directory Concurrency/
#

rm -frv *.o *.a *.so*

pwd
cd ../libnet/
make rebuild
cp -rv *.h *.a *.so ../Concurrency/

cd ../librobustio/
make rebuild
cp -rv *.h *.a *.so ../Concurrency/

cd ../Concurrency/

gcc -rdynamic concurrent_echo_server_basedon_process.c -o concurrent_echo_server_basedon_process.o -ldl

gcc -rdynamic concurrent_echo_server_basedon_select.c -o concurrent_echo_server_basedon_select.o -ldl

gcc -rdynamic echo_client.c -o echo_client.o -ldl

gcc concurrent_echo_server_basedon_eventdriven.c -o concurrent_echo_server_basedon_eventdriven.o ./libnet.so ./librobustio.so

gcc concurrent_echo_client.c -o concurrent_echo_client.o ./libnet.so ./librobustio.so

ls -l