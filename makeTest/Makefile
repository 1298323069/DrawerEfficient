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

CPPDIRS=.
CPPS=$(shell for dir in ${CPPDIRS};do echo $${dir}/*.cpp;done)

OBJDIR=obj
OBJS=$(patsubst %.cpp,${OBJDIR}/%.o,$(notdir ${CPPS}))


SUBDIRS = foo bar baz



#final target rule
$(executable): $(objects)
		$(CC) $^ -o $@ 

#static model simply makefile
$(objects):%.o:%.cpp
		$(CC) -c $< -o $@ 

#clean rule for complicated project
.PHONY: clean echo subdir
clean:
		$(RM) $(executable) $(objects) $(deps)

echo:
		$(OBJS)

subdir:
	 for dir in $(SUBDIRS);do\
          $(shell mkdir $$dir);\
        done

sinclude $(deps)
$(deps):%.d:%.cpp
		$(CC) -MM $< > $@






