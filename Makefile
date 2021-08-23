CC=gcc
CFLAGS=-Wall
OBJS = main.o

all: EduLab

EduLab: $(OBJS)

main.o: main.c

clean: 
	rm -f EduLab *.o
