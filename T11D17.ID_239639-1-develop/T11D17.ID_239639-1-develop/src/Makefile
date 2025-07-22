CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
.PHONY: all clean rebuild

all: door_struct list_test stack_test

door_struct: dmanager_module.c door_struct.h
	$(CC) $(CFLAGS) dmanager_module.c -o ../build/Quest_1

list_test: list_test.c list.c list.h door_struct.h
	$(CC) $(CFLAGS) list_test.c list.c -o ../build/Quest_2
	
stack_test: stack_test.c stack.c stack.h
	$(CC) $(CFLAGS) stack_test.c stack.c -o ../build/Quest_3

clean:
	rm -rf ../build/Quest_*

rebuild: clean all
