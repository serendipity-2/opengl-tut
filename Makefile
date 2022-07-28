LDLIBS=-lglfw -lGL -lGLEW -lm -lX11 -lpthread -lXi -lXrandr -ldl 
all: src/main 
clean:
	rm -f common/*.o src/main
src/main: common/utils.o common/controls.o
common/utils.o: common/utils.cpp common/utils.hpp
common/controls.o: common/controls.cpp common/controls.hpp
.PHONY: all clean

