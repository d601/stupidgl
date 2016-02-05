CC = gcc
CFLAGS = $(shell sdl2-config --cflags)
LDLIBS = -lGLEW -lGL $(shell sdl2-config --libs) -lm
OBJS = main.o shader.o char_buffer.o matrix.o
PROG = stupidgl
 
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)
	
main.o: main.c char_buffer.h shader.h matrix.h

shader.o: shader.h char_buffer.h

char_buffer.o: char_buffer.h

matrix.o: matrix.h

clean:
	rm -f *.o $(PROG)
