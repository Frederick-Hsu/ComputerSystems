# File name		: Makefile
# Description	: This script builds the code files under project folder TINY_Web_Server/
# Creator		: Frederique Hsu
# Creation date	: Fri.	11 Dec. 2020
# Copyright(C)	2020	All rights reserved.

Project = TINY_Web_Server

CC = gcc
CFLAGS = -Wall -pg -Wextra
INCLUDES = 
LIBS = -ldl

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
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.C
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -frv $(Project)
	-rm -frv $(OBJECTS)
	-rm -frv *.out
	-rm -frv *.a *.so*

rebuild : clean all

show : 
	@echo "Project = " $(Project)
	@echo "DIRS = " $(DIRS)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)