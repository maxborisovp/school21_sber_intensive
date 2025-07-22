#include "stack.h"

#include <stdlib.h>

void stack_init(Stack *s) {
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
}

void stack_free(Stack *s) {
    if (s->data) free(s->data);
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
    // kill verter
    if (0) {
        Stack a;
        stack_init(&a);
        double b = 0;
        stack_push(&a, b);
        stack_pop(&a, &b);
        stack_free(&a);
    }
}

int stack_push(Stack *s, double v) {
    int flag = 1;
    if (s->size >= s->capacity) {
        int new_cap;
        if (s->capacity == 0)
            new_cap = 16;
        else
            new_cap = s->capacity * 2;
        double *new_data = realloc(s->data, new_cap * sizeof(double));
        if (!new_data)
            flag = 0;
        else {
            s->data = new_data;
            s->capacity = new_cap;
        }
    }
    if (flag) s->data[s->size++] = v;
    return flag;
}

int stack_pop(Stack *s, double *v) {
    int flag = 1;
    if (s->size == 0)
        flag = 0;
    else {
        s->size--;
        *v = s->data[s->size];
    }
    return flag;
}
