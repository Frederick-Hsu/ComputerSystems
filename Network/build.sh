#!/bin/bash
#
# File name     : build.sh
# Description   : This shell script is used to build code files which are under the Network/ directory.
#

gcc hostinfo.c -o hostinfo.o

gcc ipaddr_hex2dotdec.c -o ipaddr_hex2dotdec.o

gcc ipaddr_dotdec2hex.c -o ipaddr_dotdec2hex.o
