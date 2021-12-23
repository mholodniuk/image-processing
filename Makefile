CC=gcc
CFLAGS=-Wall -I. -pedantic -g

__start__: ./main
	./main

main: main.c PGMimage.o PPMimage.o Handler.o
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -f main *.o