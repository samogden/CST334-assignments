all: clean buffer

buffer: buffer.c
	gcc -pthread -lm -o buffer buffer.c

clean:
	rm buffer

.PHONY: all clean