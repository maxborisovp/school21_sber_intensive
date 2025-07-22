CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
.PHONY: all clean rebuild

all: state_sort state_search clear_state

state_sort: state_sort.c door_state.h
	$(CC) $(CFLAGS) state_sort.c -o ../build/Quest_1

state_search: state_search.c door_state.h
	$(CC) $(CFLAGS) state_search.c -o ../build/Quest_2

clear_state: clear_state.c door_state.h
	$(CC) $(CFLAGS) clear_state.c -o ../build/Quest_3

clean:
	rm -f ../build/Quest_*

rebuild: clean all
