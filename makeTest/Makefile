#descript: this a C/C++ project
#version: 

#define executable file
executable := complicated

#define source file list
sources := $(wildcard *.cpp)

#define object file list
objects := $(sources:.cpp=.o)

#define precompile var
CC := gcc

RM := rm -rf

INC+=-I/usr/local/mysql/include
LIBDIR+=-L/usr/local/mysql/lib


#final target rule

VPATH = /usr/local/mysql/lib
$(executable): ${objects} -lmysqlclient
	${CC} ${FLAGS} $^ -o $@ 

#static model simply makefile

main.o: main.cpp
	${CC} -o $@ -c $<

mysqlhelper.o: mysqlhelper.cpp
	${CC}  ${FLAGS} ${INC} -c $< -o $@ 

#clean rule for complicated project
.PHONY: clean
clean:
		$(RM) $(executable) $(objects)





