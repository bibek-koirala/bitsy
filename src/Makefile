CC=gcc
CFLAGS=-Wall -Wextra -std=c99

OBJS=bitsy.o

all: bitsy

bitsy: $(OBJS)
	gcc -o $@ $^

bitsy.o: bitsy.c

clean:
	rm -f $(OBJS)
	rm -f bitsy