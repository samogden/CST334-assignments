CC=gcc
CFLAGS=-g -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/

# Source files and object files
SRCS = $(wildcard src/*.c)
TEST = $(wildcard tests/*.c)
OBJS = $(SRCS:src/%.c=bin/%.o)

# Header files
HEADERS = $(wildcard src/*.h)

# Target executable
TARGET = unit_tests


all: clean unit_tests
	./unit_tests -j1

# Rule to build the executable
unit_tests: unit_tests.c bin $(OBJS) $(TEST)
	$(CC) $(CFLAGS) unit_tests.c -o $@ $(OBJS)

# Rule to build the debug executable
debug: debug.c bin $(OBJS) $(TEST)
	$(CC) $(CFLAGS) debug.c -o $@ $(OBJS)

# Rule to compile .c files into .o files
bin/%.o: src/%.c $(HEADERS) $(TEST)
	$(CC) $(CFLAGS) -c $< -o $@

grade:
	python ../../helpers/grader.py

# Clean rule to remove object files and the executable
clean:
	rm -rf bin unit_tests debug

bin:
	mkdir -p bin

.PHONY: all clean grade
