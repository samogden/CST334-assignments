CC=gcc
CFLAGS=-Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/

# Source files and object files
SRCS = $(wildcard src/*.c)
TEST = $(wildcard tests/*.c)
OBJS = $(SRCS:src/%.c=bin/%.o)

# Header files
HEADERS = $(wildcard src/*.h)

all: clean debug
	./debug

# Rule to build the debug executable
debug: debug.c bin $(OBJS) $(TEST)
	$(CC) $(CFLAGS) debug.c -o $@ $(OBJS)

# Rule to compile .c files into .o files
bin/%.o: src/%.c $(HEADERS) $(TEST)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -rf bin unit_tests debug

check:
	clang-tidy -checks=bugprone-*,readability-*,-readability-identifier-length,-readability-else-after-return -warnings-as-errors=* src/student_code.c

bin:
	mkdir -p bin

.PHONY: all clean