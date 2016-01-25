all: main.o char_buffer.o shader.o
	gcc -o stupidgl.out main.o char_buffer.o shader.o -lGLEW -lGL $(shell sdl2-config --cflags --libs)
	
main.o: main.c char_buffer.h shader.h
	gcc -c main.c -lGLEW -lGL $(shell sdl2-config --cflags --libs)

shader.o: shader.c shader.h char_buffer.h
	gcc -c shader.c -lGLEW -lGL

char_buffer.o: char_buffer.c char_buffer.h
	gcc -c char_buffer.c $(shell sdl2-config --cflags --libs)

