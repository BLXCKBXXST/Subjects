CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

.PHONY: all run run-server run-client clean

all: server client

server: server.c common.h
	$(CC) $(CFLAGS) server.c -o server

client: client.c common.h
	$(CC) $(CFLAGS) client.c -o client

run: run-server

run-server: server
	./server

run-client: client
	./client

clean:
	rm -f server client request.fifo response.fifo output.txt
