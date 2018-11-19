CC=gcc
CFLAGS=-Wall -Wextra -std=c99

OBJS=bitsy.o terminal.o

all: bitsy

bitsy: $(OBJS)
	gcc -o $@ $^

bitsy.o: bitsy.c

terminal.o : terminal.c terminal.h

clean:
	rm -f $(OBJS)
	rm -f bitsy