#!/bin/bash
#
# File name     : build.sh
# Description   : This shell script is used to compile the source files under current signals/ directory,
#               : and execute them.
#


gcc send_signal.c -o send_signal.o ../../utils/libutils.so
./send_signal.o

gcc alarm.c -o alarm.o ../../utils/libutils.so

gcc sig_interrupt.c -o sig_interrupt.o ../../utils/libutils.so

gcc snooze.c -o snooze.o ../../utils/libutils.so

gcc signal_proc1.c -o signal_proc1.o ../../utils/libutils.so

gcc signal_proc2.c -o signal_proc2.o ../../utils/libutils.so

gcc signal_proc3.c -o signal_proc3.o ../../utils/libutils.so

gcc signal_proc4.c -o signal_proc4.o ../../libcsapp.so

gcc procmask.c -o procmask.o

gcc -c random_fork.c -o random_fork.o
