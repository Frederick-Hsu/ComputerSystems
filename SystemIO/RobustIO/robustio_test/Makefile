# File name		: Makefile
# Description	: This script builds the code files for project "librobustio"
# Creator		: Frederique Hsu
# Creation date : Tue.	01 Dec. 2020
# Copyright(C)	2020	All rights reserved.
#

Project = robustio_test

CC = gcc
CFLAGS = -Wall -pg
INCLUDES = 
LIBS = 

SRC_EXTENSIONS = .c .C
HDR_EXTENSIONS = .h .H

CUR_DIR = .
DIRS = $(shell find $(CUR_DIR) -maxdepth 5 -type d)
SOURCES = $(foreach dir, $(DIRS), $(wildcard $(addprefix $(dir)/*, $(SRC_EXTENSIONS))))
HEADERS = $(foreach dir, $(DIRS), $(wildcard $(addprefix $(dir)/*, $(HDR_EXTENSIONS))))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))


.PHONY : all clean rebuild show

all : $(Project)

$(Project) : $(OBJECTS)
	$(CC) $(CFLAGS) -rdynamic $^ -o $@ -ldl

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.C
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@-rm -frv $(OBJECTS)
	@-rm -frv $(Project)
	@-rm -frv *.out

rebuild : clean all

show : 
	@echo "DIRS = " $(DIRS)
	@echo "Project = " $(Project)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)