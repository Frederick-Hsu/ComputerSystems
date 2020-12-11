# File name     : build.sh
# Description   : build the source code files under nonlocl_jump/ directory, and run them.
# Creator       : Frederick Hsu
# Creation date : Sun.  29 Nov. 2020
# Copyright(C)  2020    All rights reserved.
#

gcc setjmp.c -o setjmp.o

gcc restart.c -o restart.o
