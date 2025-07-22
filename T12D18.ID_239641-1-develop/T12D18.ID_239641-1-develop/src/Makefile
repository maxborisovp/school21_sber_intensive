CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
.PHONY: all clean rebuild print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

print_module: main_module_entry_point.c print_module.h print_module.c
	$(CC) $(CFLAGS) -D PRINT_MODULE main_module_entry_point.c print_module.c -o ../build/Quest_1

documentation_module: main_module_entry_point.c print_module.h print_module.c documentation_module.c documentation_module.h
	$(CC) $(CFLAGS) -D DOC_MODULE main_module_entry_point.c print_module.c documentation_module.c -o ../build/Quest_2

bst_create_test: bst.h bst.c bst_create_test.c
	$(CC) $(CFLAGS) bst.c bst_create_test.c -o ../build/Quest_3

bst_insert_test: bst.h bst.c bst_insert_test.c
	$(CC) $(CFLAGS) bst.c bst_insert_test.c -o ../build/Quest_4

bst_traverse_test: bst.h bst.c bst_traverse_test.c
	$(CC) $(CFLAGS) bst.c bst_traverse_test.c -o ../build/Quest_5

clean:
	rm -rf ../build/Quest_*

rebuild: clean all
