all: main.o char_buffer.o shader.o matrix.o
	gcc -o stupidgl.out main.o char_buffer.o shader.o matrix.o -lGLEW -lGL $(shell sdl2-config --cflags --libs) -lm
	
main.o: main.c char_buffer.h shader.h matrix.h
	gcc -c main.c -lGLEW -lGL $(shell sdl2-config --cflags --libs) -lm

shader.o: shader.c shader.h char_buffer.h
	gcc -c shader.c -lGLEW -lGL

char_buffer.o: char_buffer.c char_buffer.h
	gcc -c char_buffer.c $(shell sdl2-config --cflags --libs)

matrix.o: matrix.c matrix.h
	gcc -c matrix.c
