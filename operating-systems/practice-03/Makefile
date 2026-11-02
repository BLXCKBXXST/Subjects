CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

all: practice

practice: main.c
	$(CC) $(CFLAGS) main.c -o practice

run: practice
	./practice

clean:
	rm -f practice output.txt
