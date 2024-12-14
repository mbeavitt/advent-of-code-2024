CFLAGS=-ggdb3

main: main.o
	gcc $(CFLAGS) -o main main.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

test: main
	./main input.txt
