#!/bin/sh
#
# File name     : build.sh
# Description   : This shell script is used to build the source code files under SystemIO/ directory.
# Creator       : Frederique Hsu
# Creation date : Mon.  30 Nov. 2020
# Copyright(C)  2020    All rights reserved.
#

gcc manip_file.c -o manip_file

gcc std_in_out.c -o std_in_out