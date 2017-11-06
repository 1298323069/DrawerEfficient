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

CFLAGS= -I/usr/local/Cellar/opencv/3.3.1_1/include/opencv -I/usr/local/include/opencv2/core/

LDFLAGS := -L/usr/local/lib

LIBS    := -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_calib3d -lopencv_ccalib -lopencv_core \
-lopencv_datasets -lopencv_dnn -lopencv_dpm -lopencv_face -lopencv_features2d -lopencv_flann -lopencv_fuzzy \
-lopencv_highgui -lopencv_img_hash -lopencv_imgcodecs -lopencv_imgproc -lopencv_line_descriptor -lopencv_ml \
-lopencv_objdetect -lopencv_optflow -lopencv_phase_unwrapping -lopencv_photo -lopencv_plot -lopencv_reg \
-lopencv_rgbd -lopencv_saliency -lopencv_shape -lopencv_stereo -lopencv_stitching -lopencv_structured_light \
-lopencv_superres -lopencv_surface_matching -lopencv_text -lopencv_tracking -lopencv_video -lopencv_videoio \
-lopencv_videostab -lopencv_xfeatures2d -lopencv_ximgproc -lopencv_xobjdetect -lopencv_xphoto

RM := rm -rf


#/usr/local/Cellar/opencv/3.3.1_1/include/opencv2

#/usr/local/Cellar/opencv/3.3.1_1/lib  libopencv_video.dylib

#final target rule


#VPATH = /usr/local/Cellar/opencv/3.3.1_1/lib
$(executable): ${objects} 

	${CC} $(LDFLAGS) $(LIBS) -o $@ $^  

#static model simply makefile


main.o: main.cpp
	${CC} ${CFLAGS} -o $@ -c $<


#clean rule for complicated project
.PHONY: clean
clean:
		$(RM) $(executable) $(objects)





