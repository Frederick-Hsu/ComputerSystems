#!/bin/sh

# File          : build.sh
# Description   : The build script on how to build current project.
#

gcc -O2 -m32 -g -o p main.c swap.c

objdump -d p > link_disassembly.txt