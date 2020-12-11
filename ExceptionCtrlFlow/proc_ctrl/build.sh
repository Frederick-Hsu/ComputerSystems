#!/bin/bash

# File name     : build.sh
# Description   : This script will build and compile the project "proc_ctrl" 
# 

gcc reap_children_processes.c -o reap_children_processes.o ../../liberror/liberror.so
# ./reap_children_processes.o

sleep 2

gcc sequentially_reap_children_processes.c -o sequentially_reap_children_processes.o ../../liberror/liberror.so
./sequentially_reap_children_processes.o


gcc shellex.c -o shellex.o ../../liberror/liberror.so
