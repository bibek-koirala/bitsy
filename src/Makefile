CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g

OBJS=bitsy.o terminal.o buffer.o input.o output.o file.o

all: bitsy

bitsy: $(OBJS)
	gcc -o $@ $^

bitsy.o: bitsy.c

terminal.o : terminal.c terminal.h

buffer.o : buffer.c buffer.h

input.o : input.c input.h

output.o : output.c output.h

file.o : file.c file.h

clean:
	rm -f $(OBJS)
	rm -f bitsy