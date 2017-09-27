#descript: this a C/C++ project
#version: 

#define executable file
executable := complicated

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


VPATH = /usr/local/mysql/include
main.o: main.cpp mysql.h
	${CC}  -o $@ -c $<

mysqlhelper.o: mysqlhelper.cpp
	${CC} ${CFLAGS} -o $@ -c $^ 

#clean rule for complicated project
.PHONY: clean
clean:
		$(RM) $(executable) $(objects)





