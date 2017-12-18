# Makefile for hello.c
hello: hello.o morning.o
	gcc -Wall -O2 -o hello hello.o morning.o

hello.o: hello.c
	gcc -c hello.c

morning.o: morning.c
	gcc -c morning.c

.PHONY: clean
clean:
	rm -f hello hello.o print.o