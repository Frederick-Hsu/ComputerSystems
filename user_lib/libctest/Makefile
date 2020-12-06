# File name		: Makefile
#

Project = libctest.so libctest.a

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

.PHONY : lib clean rebuild show install

lib : $(Project)

libctest.a : $(OBJECTS)
	ar rcs $@ $^

libctest.so : $(OBJECTS)
	# $(CC) $(CFLAGS) -shared -Wl,-soname,$@.1 -o $@.1.0 $^
	# ln -sf $@.1.0 $@.1
	# ln -sf $@.1.0 $@
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

%.o : %.C
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean :
	@-rm -frv $(OBJECTS)
	@-rm -frv $(Project)
	@-rm -frv *.so.*
	@-rm -frv *.out

rebuild : clean lib

show :
	@echo "DIRS = " $(DIRS)
	@echo "Project = " $(Project)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)

install :
	cp *.h *.so* *.a ../test/