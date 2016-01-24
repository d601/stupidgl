all:
	gcc -lGLEW -lGL main.c $(shell sdl2-config --cflags --libs) -o stupidgl.out
