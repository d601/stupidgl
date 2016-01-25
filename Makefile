all: main.o char_buffer.o
	gcc -o stupidgl.out main.o char_buffer.o -lGLEW -lGL $(shell sdl2-config --cflags --libs)
	
main.o: main.c
	gcc -c main.c -lGLEW -lGL $(shell sdl2-config --cflags --libs)

char_buffer.o: char_buffer.c char_buffer.h
	gcc -c char_buffer.c $(shell sdl2-config --cflags --libs)

