# File name		: Makefile
# Description	: This script tells how to build the liberror project.
# Creator		: Frederick Hsu
# Creation date : Tue.	10 Nov. 2020
# Copyright(C)	2020	All rights reserved.
#

TARGET = liberror.so
ARTARGET = liberror.a

CC = gcc
CFLAGS = -Wall -g -std=c11
LIBS = -lpthread

SRC_EXTENSIONS = .c .C
HDR_EXTENSIONS = .h .H
ASM_EXTENSIONS = .s

CURRENT_DIR = .
DIRS = $(shell find $(CURRENT_DIR) -maxdepth 4 -type d)
SOURCES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(SRC_EXTENSIONS)))
HEADERS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(HDR_EXTENSIONS)))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

.PHONY: lib clean rebuild 

lib : $(TARGET) $(ARTARGET)

# $^ : designate all the $(OBJECTS)
# $@ : designate the single $(TARGET) or $(ARTARGET)

$(TARGET) : $(OBJECTS)
	# @echo "$$^ = " $^
	# @echo "$$ @ = " $@
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@ $(LIBS)

$(ARTARGET) : $(OBJECTS)
	ar rcs $@ $^

# #< : designate each source file (%.c)
%.o : %.c
	# @echo "$$< = " $<
	# @echo "$$ @ = " $@
	$(CC) $(CFLAGS) -shared -fPIC -c $< -o $@

%.o : %.C
	$(CC) $(CFLAGS) -shared -fPIC -c $< -o $@

clean:
	@find . -name "*.o" -exec rm -frv {} \;
	@-rm -frv $(TARGET)
	@-rm -frv $(ARTARGET)

rebuild : clean lib