CC = gcc
CCFLAGS = -g -Wall -Werror

%.o: %.c
	$(CC) -c $(CCFLAGS) $<

all: main

main: main.o
	$(CC) -o $@ main.o

clean:
	$(RM) *.o *.swp foo.c main 
