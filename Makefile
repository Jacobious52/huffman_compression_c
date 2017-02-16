all: main

main: main.c pq.h pq.c huffman.h huffman.c
	gcc main.c pq.c huffman.c -Wall -Wextra -pedantic -O2 -o main
