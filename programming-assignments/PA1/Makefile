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
CFLAGS=-g -Wall -lcriterion -I/opt/homebrew/include/ -I../common/ -I$(INCLUDE_DIR)

# Target executable name
TARGET = unit_tests

# Build all
all: clean build_debug unit_tests
	./unit_tests -j1 --timeout 10

# Rule to build the executable
unit_tests: clean unit_tests.c bin $(OBJS) $(TEST)
	$(CC) $(CFLAGS) unit_tests.c -o $@ $(OBJS)

# Rule to build the debug executable
build_debug: clean debug.c bin $(OBJS) $(TEST)
	$(CC) $(CFLAGS) debug.c -o debug $(OBJS)

# Rule to build the debug executable
debug: clean build_debug
	gdb ./debug

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
	clang-tidy -checks=bugprone-*,readability-*,-readability-identifier-length,-readability-else-after-return,-bugprone-easily-swappable-parameters,-readability-redundant-control-flow,-readability-non-const-parameter,-clang-analyzer-security* -warnings-as-errors=bugprone-*,readability-* src/student_code.c -- -I$(INCLUDE_DIR) -I../common/

bin:
	mkdir -p bin

.PHONY: all clean grade build_debug
	
.INTERMEDIATE: .build_debug
