#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void init(struct stack* mystack) { mystack->top = NULL; }

void push(struct stack* mystack, int n) {
    struct stack_node* new_node = malloc(sizeof(struct stack_node));
    new_node->number = n;
    new_node->pred = mystack->top;
    mystack->top = new_node;
}

void pop(struct stack* mystack) {
    if (mystack->top != NULL) {
        struct stack_node* tmp = mystack->top;
        mystack->top = tmp->pred;
        free(tmp);
    }
}

void output(struct stack* mystack) {
    if (mystack->top == NULL)
        printf("stack pust");
    else {
        struct stack_node* cur = mystack->top;
        while (cur != NULL) {
            printf("%d", cur->number);
            if (cur->pred != NULL) printf(" ");
            cur = cur->pred;
        }
    }
}

void destroy(struct stack* mystack) {
    if (mystack->top != NULL) {
        struct stack_node* tmp = mystack->top;
        while (tmp != NULL) {
            mystack->top = tmp->pred;
            free(tmp);
            tmp = mystack->top;
        }
    }
}
