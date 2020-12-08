CC = gcc
CFLAGS = -Wall
LDFLAGS =
SERVER_SRC = server.c
CLIENT_SRC = client.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: server client

server: $(SERVER_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

client: $(CLIENT_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run_server run_client

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) server client

run_server: server
	./server

run_client: client
	./client
