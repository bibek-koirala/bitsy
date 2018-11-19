CC=gcc
CFLAGS=-Wall -Wextra -std=c99

OBJS=bitsy.o terminal.o input.o output.o

all: bitsy

bitsy: $(OBJS)
	gcc -o $@ $^

bitsy.o: bitsy.c

terminal.o : terminal.c terminal.h

input.o : input.c input.h

output.o : output.c output.h

clean:
	rm -f $(OBJS)
	rm -f bitsy