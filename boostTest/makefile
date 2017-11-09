#descript: this a C/C++ project
#version: 

#define executable file
executable := mysql.out

#define source file list
sources := $(wildcard *.cpp)

#define object file list
objects := $(sources:.cpp=.o)

#define precompile var

CC=g++  

CFLAGS= -I/usr/local/Cellar/boost/1.65.1/include/boost

LDFLAGS := -L/usr/local/lib

LIBS    :=  -lboost_atomic -lboost_chrono -lboost_container -lboost_context -lboost_coroutine \
-lboost_date_time -lboost_exception -lboost_filesystem -lboost_graph -lboost_iostreams -lboost_locale \
-lboost_log -lboost_log_setup -lboost_math_c99 -lboost_math_c99f -lboost_math_c99l -lboost_math_tr1 \
-lboost_math_tr1f -lboost_math_tr1l -lboost_numpy -lboost_prg_exec_monitor  -lboost_random \
-lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_test_exec_monitor -lboost_thread \
-lboost_timer -lboost_type_erasure -lboost_unit_test_framework -lboost_wave -lboost_wserialization -lboost_python


RM := rm -rf

#final target rule

$(executable): ${objects} 
	${CC} $(LDFLAGS) $(LIBS) -o $@ $^  

#static model simply makefile


main.o: main.cpp
	${CC} ${CFLAGS} -o $@ -c $<


#clean rule for complicated project
.PHONY: clean
clean:
		$(RM) $(executable) $(objects)





