#ifndef STACK_H
#define STACK_H

struct stack_node {
    int number;
    struct stack_node* pred;
};
struct stack {
    struct stack_node* top;
};

void init(struct stack* mystack);
void push(struct stack* mystack, int n);
void pop(struct stack* mystack);
void output(struct stack* mystack);
void destroy(struct stack* mystack);

#endif
