#descript: this a C/C++ project
#version: 

#define executable file
executable := a.out

#define source file list
sources := $(wildcard *.cpp)

#define object file list
objects := $(sources:.cpp=.o)

#define precompile var

CC=g++  

CFLAGS=-I/usr/local/mysql/include 


RM := rm -rf

#final target rule

VPATH = /usr/local/mysql/lib
$(executable): ${objects} -lmysqlclient 
	${CC} ${CFLAGS} $^ -o $@ 

#static model simply makefile


main.o: main.cpp
	${CC} ${CFLAGS} -o $@ -c $<


mysqlhelper.o: mysqlhelper.cpp

	${CC} ${CFLAGS} -o $@ -c $< 

#clean rule for complicated project
.PHONY: clean
clean:
		$(RM) $(executable) $(objects)





