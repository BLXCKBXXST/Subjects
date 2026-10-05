CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

.PHONY: all run run1 run2 clean

all: practice

practice: main.c practice.h
	$(CC) $(CFLAGS) main.c -o practice

run: practice
	./practice -1 -f example.txt

run1: practice
	./practice -1

run2: practice
	./practice -2

clean:
	rm -f practice
