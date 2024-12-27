CFLAGS = -ggdb3

main: main.o matrix.o solutions.o
	gcc $(CFLAGS) -o main main.o matrix.o solutions.o

main.o: main.c matrix.h solutions.h
	gcc $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h
	gcc $(CFLAGS) -c matrix.c

solutions.o: solutions.c solutions.h
	gcc $(CFLAGS) -c solutions.c

test: main
	./main test.txt
