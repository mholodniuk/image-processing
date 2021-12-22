CC=gcc
CFLAGS=-Wall -I. -pedantic -g

__start__: ./main
	./main

main: main.c
	${CC} ${CFLAGS} -o main  main.c 