CC = gcc
CFLAGS = -Wall
# Modify the below to this: MAIN=main_program_name
MAIN=main 

all: ${MAIN}

${MAIN}: myllist.o ${MAIN}.o
	${CC} $^ -o $@
	
${MAIN}.o: ${MAIN}.c
	${CC} -c $< -o $@

myllist.o: src/myllist.c include/myllist.h
	${CC} -c $< -o $@

clean:
	rm *.o main
