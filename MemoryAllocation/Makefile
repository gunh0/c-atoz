CC=gcc
CFLAGS=-Wall -pthread

all: main

main: main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main

run:
	./main
