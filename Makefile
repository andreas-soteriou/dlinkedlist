CC = gcc
CFLAGS = -Wall

all: main

main: myllist.o main.o
	${CC} $^ -o $@
	
main.o: main.c
	${CC} -c $< -o $@

myllist.o: src/myllist.c include/myllist.h
	${CC} -c $< -o $@

clean:
	rm *.o main
