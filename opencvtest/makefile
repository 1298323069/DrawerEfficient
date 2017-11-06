#descript: this a C/C++ project
#version: 

#define executable file
executable := testcv.out

#define source file list
sources := $(wildcard *.cpp)

#define object file list
objects := $(sources:.cpp=.o)

#define precompile var

CC=g++  

CFLAGS= -I/usr/local/Cellar/opencv/3.3.1_1/include/opencv2 


RM := rm -rf


#/usr/local/Cellar/opencv/3.3.1_1/include/opencv2

#/usr/local/Cellar/opencv/3.3.1_1/lib  libopencv_video.dylib

#final target rule


VPATH = /usr/local/Cellar/opencv/3.3.1_1/lib
$(executable): ${objects} -lopencv_video.3.3.1
	${CC} ${CFLAGS} $^ -o $@ 

#static model simply makefile


main.o: main.cpp
	${CC} ${CFLAGS} -o $@ -c $<


#clean rule for complicated project
.PHONY: clean
clean:
		$(RM) $(executable) $(objects)





