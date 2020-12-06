# File name		: Makefile
# Description	: This script is used to build the utils project to produce libutils.
# Creator		: Frederique Hsu
# Creation date : Sat.	21 Nov. 2020
# Copyright(C)	2020	All rights reserved.
#

Project = libutils.so libutils.a

CC = gcc
CFLAGS = -Wall -pg
LIBS = -lpthread


SRC_EXTENSIONS = .c .C
HDR_EXTENSIONS = .h .H
ASM_EXTENSIONS = .s .asm


CUR_DIR = .
DIRS = $(shell find $(CUR_DIR) -maxdepth 4 -type d)
SOURCES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(SRC_EXTENSIONS)))
HEADERS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(HDR_EXTENSIONS)))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

.PHONY : lib clean rebuild install distribution show

lib : $(Project)

libutils.so : $(OBJECTS)
	# @echo "$$^ = " $^
	# @echo "$$@ = " $@
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@ $(LIBS)

libutils.a : $(OBJECTS)
	# @echo "$$^ = " $^
	# @echo "$$@ = " $@
	ar rcs $@ $^

%.o : %.c
	# @echo "$$< = " $<
	# @echo "$$@ = " $@
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

%.o : %.C
	# @echo "$$< = " $<
	# @echo "$$@ = " $@
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean :
	@find . -name "*.o" -exec rm -frv {} \;
	@-rm -frv $(Project)

rebuild : clean lib

show :
	@echo "DIRS = " $(DIRS)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)
