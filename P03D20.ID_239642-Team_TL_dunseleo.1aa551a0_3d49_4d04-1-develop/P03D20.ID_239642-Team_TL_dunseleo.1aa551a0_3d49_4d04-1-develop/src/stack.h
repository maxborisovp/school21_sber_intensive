#ifndef STACK_H
#define STACK_H

typedef struct {
    double *data;
    int size;
    int capacity;
} Stack;
void stack_init(Stack *s);
void stack_free(Stack *s);
int stack_push(Stack *s, double v);
int stack_pop(Stack *s, double *v);

#endif
