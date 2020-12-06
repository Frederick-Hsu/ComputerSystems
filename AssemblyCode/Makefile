TARGET = AssemblyCode


CC = gcc
CFLAGS = -Wall -std=c11 # -march=i686
LIBS = 

SRCEXTS = .c .C
HDREXTS = .h .H

CURRENT_DIR = .
DIRS = $(shell find $(CURRENT_DIR) -maxdepth 4 -type d)
SOURCES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(SRCEXTS)))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))
ASMOBJS = $(addsuffix .s, $(basename $(SOURCES)))

.PHONY : all clean show rebuild disassembly assembly

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@find . -name "*.o" -exec rm -frv {} \;
	@find . -name "*.s" -exec rm -frv {} \;
	@-rm -frv $(TARGET)
	@-rm -frv $(TARGET)_disassembly.txt

rebuild : clean all

show :
	@echo "DIRS : " $(DIRS)
	@echo "SOURCES : " $(SOURCES)
	@echo "OBJECTS : " $(OBJECTS)
	@echo "TARGET : " $(TARGET)

assembly : $(ASMOBJS)
%.s : %.c
	$(CC) $(CFLAGS) -S $< -o $@

disassembly :
	objdump -d $(TARGET) > $(TARGET)_disassembly.txt