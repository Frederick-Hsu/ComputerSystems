#!/bin/sh

# File          : build.sh
# Description   : The build script on how to build current project.
#

gcc -O2 -m32 -g -o p.o main.c swap.c

objdump -d p.o > link_disassembly.txt
