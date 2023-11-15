CC=gcc
CFLAGS=-g -Wall -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -lcriterion

# Source files and object files
SRCS = $(wildcard src/*.c)
TEST = $(wildcard tests/*.c)
OBJS = $(SRCS:src/%.c=bin/%.o)

# Header files
HEADERS = $(wildcard src/*.h)

# Target executable
TARGET = server


all: clean server client


# Rule to build the executable
server: ./src/server.c bin/queue.o
	$(CC) $(CFLAGS) ./src/server.c -o server bin/queue.o

# Rule to build the executable
client: ./src/client.c
	$(CC) $(CFLAGS) ./src/client.c -o client


# Rule to compile .c files into .o files
bin/queue.o: bin src/queue.c src/queue.h
	$(CC) $(CFLAGS) -c src/queue.c -o bin/queue.o


# Clean rule to remove object files and the executable
clean:
	rm -rf bin debug

bin:
	mkdir -p bin

.PHONY: all clean grade
