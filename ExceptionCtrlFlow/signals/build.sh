#!/bin/bash
#
# File name     : build.sh
# Description   : This shell script is used to compile the source files under current signals/ directory,
#               : and execute them.
#


gcc send_signal.c -o send_signal ../../utils/libutils.so
./send_signal

gcc alarm.c -o alarm ../../utils/libutils.so

gcc sig_interrupt.c -o sig_interrupt ../../utils/libutils.so

gcc snooze.c -o snooze ../../utils/libutils.so

gcc signal_proc1.c -o signal_proc1 ../../utils/libutils.so

gcc signal_proc2.c -o signal_proc2 ../../utils/libutils.so

gcc signal_proc3.c -o signal_proc3 ../../utils/libutils.so

gcc signal_proc4.c -o signal_proc4 ../../libcsapp.so

gcc procmask.c -o procmask

gcc -c random_fork.c -o random_fork