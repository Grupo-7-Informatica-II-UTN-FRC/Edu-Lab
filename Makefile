CC=gcc
CFLAGS=-Wall


main: main.o
main.o: main.c

clean: 
	rm -f main *.o
