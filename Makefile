CC=gcc
CFLAGS=-Wall -I. -pedantic -g

__start__: main
	./main.out

main: main.c
	${CC} ${CFLAGS} -o main.out  main.c 