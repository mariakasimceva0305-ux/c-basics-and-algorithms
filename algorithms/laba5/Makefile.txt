CC = gcc
CFLAGS = -Wall -std=c99 -g
LIBS = -lm

all: program test

program:
	$(CC) $(CFLAGS) -Iinclude src/main.c src/lrps.c -o program $(LIBS)

test:
	$(CC) $(CFLAGS) -Iinclude test/test.c src/lrps.c -o test_program $(LIBS)

clean:
	rm -f program test_program

run: program
	./program

test-run: test
	./test_program

.PHONY: all clean run test-run