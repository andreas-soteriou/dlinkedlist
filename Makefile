CC = gcc
CFLAGS = -Wall
# Modify the below to this: MAIN=main_program_name
MAIN = main

all: ${MAIN}

${MAIN}: myllist.o main.o
	${CC} $^ -o $@

${MAIN}.o: ${MAIN}.c
	${CC} -c $< -o $@

myllist.o: src/myllist.c
	${CC} -c $< -o $@

clean:
	rm -f *.o ${MAIN}
