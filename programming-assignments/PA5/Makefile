# Set directories up
SRC_DIR := ./src
BUILD_DIR := ./bin
INCLUDE_DIR := ./include
TESTS_DIR := ./tests

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST = $(wildcard $(TESTS_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS = $(wildcard include/*.h)

# Compiler flags
CC=gcc
CFLAGS=-g -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -I../common/ -I$(INCLUDE_DIR)

# Target executable name
TARGET = unit_tests

# Build all
all: clean debug unit_tests
	./unit_tests -j1 --timeout 30

# Rule to build the executable
unit_tests: clean unit_tests.c bin $(OBJS) $(TEST)
	$(CC) $(CFLAGS) unit_tests.c -o $@ $(OBJS)

# Rule to build the debug executable
debug: clean debug.c bin $(OBJS) $(TEST)
	$(CC) $(CFLAGS) debug.c -o $@ $(OBJS)

# Rule to compile .c files into .o files
bin/%.o: src/%.c $(HEADERS) $(TEST)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the grader
grade:
	python ../../helpers/grader.py

# Clean rule to remove object files and the executable
clean:
	rm -rf bin unit_tests debug

check:
	clang-tidy -checks=bugprone-*,readability-*,-readability-identifier-length,-readability-else-after-return -warnings-as-errors=* src/student_code.c

bin:
	mkdir -p bin

.PHONY: all clean grade
