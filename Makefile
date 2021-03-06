CC = gcc
CFLAGS = $(shell sdl2-config --cflags) -Wpointer-sign -Wreturn-type
LDLIBS = -lGLEW -lGL $(shell sdl2-config --libs) -lm
OBJS = main.o shader.o char_buffer.o matrix.o stupid_engine.o renderable.o entity.o
PROG = stupidgl
 
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)
	
main.o: stupid_engine.h

stupid_engine.o: stupid_engine.h char_buffer.h shader.h matrix.h entity.h

shader.o: shader.h char_buffer.h

char_buffer.o: char_buffer.h common.h

matrix.o: matrix.h

entity.o: entity.h renderable.h

renderable.o: renderable.h

clean:
	rm -f *.o $(PROG)
