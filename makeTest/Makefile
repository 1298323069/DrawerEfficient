#descript: this a C/C++ project
#version: 

#define executable file
executable := complicated

#define source file list
sources := $(wildcard *.cpp)

#define object file list
objects := $(sources:.cpp=.o)

#define depend descript file list
deps := $(sources:.cpp=.d)

#define precompile var
CC := gcc

RM := rm -rf

#final target rule
$(executable): $(objects)
		$(CC) -o $@ $^

#static model simply makefile
$(objects):%.o:%.cpp
		$(CC) -o $@ -c $<

#clean rule for complicated project
.PHONY: clean
clean:
		$(RM) $(executable) $(objects) $(deps)

sinclude $(deps)
$(deps):%.d:%.cpp
		$(CC) -MM $< > $@






