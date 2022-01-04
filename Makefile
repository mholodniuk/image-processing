CC=gcc
CFLAGS=-Wall -I. -pedantic -g

__start__: ./main
	./main

main: ppm.c  PPMimage.o Handler.o
	${CC} ${CFLAGS} -o $@ $^ -lm

%.o: %.c
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -f main *.o