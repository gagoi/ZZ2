all: prog

main.o: main.c
	gcc -c main.c

mt19937ar.o: mt19937ar.c
	gcc -c mt19937ar.c

prog: mt19937ar.o main.o
	gcc -o prog mt19937ar.o main.o -Wall -Wextra -O2 -lm

clean:
	rm *.o
	rm prog