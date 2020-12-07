# File name		: Makefile
# Description	: This script builds the code files for project "librobustio"
# Creator		: Frederique Hsu
# Creation date : Tue.	01 Dec. 2020
# Copyright(C)	2020	All rights reserved.
#

Project = librobustio.so librobustio.a

CC = gcc
CFLAGS = -Wall -pg -Wextra
INCLUDES = 
LIBS = 

SRC_EXTENSIONS = .c .C
HDR_EXTENSIONS = .h .H

CUR_DIR = .
DIRS = $(shell find $(CUR_DIR) -maxdepth 5 -type d)
SOURCES = $(foreach dir, $(DIRS), $(wildcard $(addprefix $(dir)/*, $(SRC_EXTENSIONS))))
HEADERS = $(foreach dir, $(DIRS), $(wildcard $(addprefix $(dir)/*, $(HDR_EXTENSIONS))))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))


.PHONY : lib clean rebuild show install

lib : $(Project)

librobustio.so : $(OBJECTS)
	$(CC) $(CFLAGS) -shared -Wl,-soname=$@.1 -o $@.1.0.0 $^
	-ln -sf $@.1.0.0 $@.1.0
	-ln -sf $@.1.0.0 $@.1
	-ln -sf $@.1.0.0 $@

librobustio.a : $(OBJECTS)
	ar rcs $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

%.o : %.C
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean :
	@-rm -frv $(OBJECTS)
	@-rm -frv $(Project)
	@-rm -frv *.out
	@-rm -frv *.so.*

rebuild : clean lib

show : 
	@echo "DIRS = " $(DIRS)
	@echo "Project = " $(Project)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)

install :
	-cp robust_io.h $(Project) *.so* ../client/
	-cp robust_io.h $(Project) *.so* ../server/