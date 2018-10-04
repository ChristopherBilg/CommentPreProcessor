output: main.o
	gcc main.o -o output -lm -g

main.o: main.c
	gcc -c main.c -lm -g
