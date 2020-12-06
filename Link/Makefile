# File name 	: Makefile
# Description	: This script is used to build current project Link
#

EXECUTABLE = Link

CC = gcc
CFLAGS = -Wall -std=c11

CPPC = g++
CPPFLAGS = -Wall -std=c++17 -g
LIBS = 


SRC_EXTENSIONS = .c .cpp .cxx .cc .C
HDR_EXTENSIONS = .h .hpp .H
ASM_EXTENSIONS = .s .asm

CUR_DIR = .
DIRS = $(shell find $(CUR_DIR) -maxdepth 4 -type d)
SOURCES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(SRC_EXTENSIONS)))
HEADERS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(HDR_EXTENSIONS)))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))
ASSEMBLIES = $(addsuffix .s, $(basename $(SOURCES)))

.PHONY : all clean show rebuild disassembly assembly


all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.C
	$(CC) $(CFLAGS) -c $< -o $@

# %.o : %.cpp
# 	$(CPPC) $(CPPFLAGS) -c $< -o $@

# %.o : %.cxx
# 	$(CPPC) $(CPPFLAGS) -c $< -o $@

# %.o : %.cc
# 	$(CPPC) $(CPPFLAGS) -c $< -o $@

clean :
	@find . -name "*.o" -exec rm -frv {} \;
	@find . -name "*.s" -exec rm -frv {} \;
	@-rm -frv $(EXECUTABLE)
	@-rm -frv $(EXECUTABLE)_disassembly.txt

rebuild : clean all

show : 
	@echo "DIRS = " $(DIRS)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)
	@ECHO "EXECUTABLE = " $(EXECUTABLE)

assembly : $(ASSEMBLIES)
%.s : %.c
	$(CC) $(CFLAGS) -S $< -o $@

disassembly :
	objdump -d $(EXECUTABLE) > $(EXECUTABLE)_disassembly.txt