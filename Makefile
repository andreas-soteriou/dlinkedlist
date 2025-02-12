CC = gcc
CFLAGS = -Wall
# Modify the below to this: MAIN=main_program_name
MAIN = main

all: ${MAIN}

${MAIN}: dllist.o main.o
	${CC} $^ -o $@

${MAIN}.o: ${MAIN}.c
	${CC} -c $< -o $@

dllist.o: src/dllist.c
	${CC} -c $< -o $@

clean:
	rm -f *.o ${MAIN}
