#include "print_module.h"

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char* message) {
    int i = 0;
    while (message[i] != '\0') {
        print(message[i]);
        i++;
    }
}
