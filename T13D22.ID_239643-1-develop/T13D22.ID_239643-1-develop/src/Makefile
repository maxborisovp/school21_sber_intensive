CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
.PHONY: all clean rebuild

all: cipher

cipher: cipher.c
	$(CC) $(CFLAGS) cipher.c -o ../build/cipher -lssl -lcrypto

clean:
	rm -f ../build/cipher

rebuild: clean all

