# File name		: Makefile
# Description	: This script builds the code files under the directory libnet to produce the libnet.so shared library.
#

Project = libnet.a libnet.so

CC = gcc
CFLAGS = -Wall -g
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

libnet.a : $(OBJECTS)
	ar rcs $@ $^

libnet.so : $(OBJECTS)
	$(CC) $(CFLAGS) -shared -Wl,-soname=$@.1 -o $@.1.0.0 $^
	-ln -sf $@.1.0.0 $@.1.0
	-ln -sf $@.1.0.0 $@.1
	-ln -sf $@.1.0.0 $@

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

%.o : %.C
	$(CC) $(CFLAGS) -fPIC -c $< -o -$@

clean :
	@-rm -frv $(OBJECTS)
	@-rm -frv $(Project)
	@-rm -frv *.so*
	@-rm -frv *.out

rebuild : clean lib

show :
	@echo "Project = " $(Project)
	@echo "DIRS = " $(DIRS)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)