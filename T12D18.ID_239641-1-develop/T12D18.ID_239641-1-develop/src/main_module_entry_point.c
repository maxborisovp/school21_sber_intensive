#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "print_module.h"

#ifdef DOC_MODULE
#include "documentation_module.h"

void output_availability(int *data, ...);
#endif

int main() {
#ifdef PRINT_MODULE
    char time_str[9];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", localtime(&(time_t){time(NULL)}));
    print_log(print_char, Log_prefix);
    print_log(print_char, " ");
    print_log(print_char, time_str);
    print_log(print_char, " ");
    print_log(print_char, Module_load_success_message);
#endif
#ifdef DOC_MODULE
    int availability_mask[MAX_DOCS];
    check_available_documentation_module(availability_mask, validate, Documents_count, Documents);
    // Output availability for each document....
    output_availability(availability_mask, Documents);
#endif
    return 0;
}
#ifdef DOC_MODULE
void output_availability(int *data, ...) {
    va_list docs;
    va_start(docs, data);
    for (int i = 0; i < Documents_count; i++) {
        print_log(print_char, va_arg(docs, char *));
        if (data[i])
            print_log(print_char, ": available");
        else
            print_log(print_char, ": unavailable");
        if (i != Documents_count - 1) print_log(print_char, "\n");
    }
    va_end(docs);
}
#endif
