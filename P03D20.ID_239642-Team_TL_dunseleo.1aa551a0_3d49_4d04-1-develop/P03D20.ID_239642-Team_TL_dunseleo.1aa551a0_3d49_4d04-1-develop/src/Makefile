CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
.PHONY: all clean rebuild

all: graph.c parsing.c parsing.h stack.c stack.h token.c token.h polish_notation.c polish_notation.h
	$(CC) $(CFLAGS) graph.c parsing.c token.c stack.c polish_notation.c -o ../build/graph

clean:
	rm -rf ../build/graph

rebuild: clean all
