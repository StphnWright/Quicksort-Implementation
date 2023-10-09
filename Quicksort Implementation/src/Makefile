CC = gcc
CFLAGS = -g -Wall -Werror -pedantic-errors

all: sort

sort: sort.o quicksort.o
	$(CC) $(CFLAGS) sort.o quicksort.o -o sort

quicksort.o: quicksort.c quicksort.h
	$(CC) $(CFLAGS) -c quicksort.c

.PHONY: clean
clean:
	rm -f sort *.o
