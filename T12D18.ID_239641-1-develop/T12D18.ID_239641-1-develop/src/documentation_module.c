#include "documentation_module.h"

#include <stdarg.h>

int validate(char* data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int* check_available_documentation_module(int* check_data, int (*validate)(char*), int document_count, ...) {
    va_list docs;
    va_start(docs, document_count);
    for (int i = 0; i < document_count; i++) {
        if (validate(va_arg(docs, char*))) {
            check_data[i] = 1;
        } else {
            check_data[i] = 0;
        }
    }
    va_end(docs);
    return check_data;
}
