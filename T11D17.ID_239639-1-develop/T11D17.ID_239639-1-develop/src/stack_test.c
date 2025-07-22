#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
void push_tests(struct stack* mystack);
void pop_tests(struct stack* mystack);

int main() {
    struct stack mystack;

    init(&mystack);
    push_tests(&mystack);
    pop_tests(&mystack);
    destroy(&mystack);
    return 0;
}

void push_tests(struct stack* mystack) {
    printf("TESTS to push in stack\n");

    printf("Test1 add 1 in stack\n");
    push(mystack, 1);
    printf("Output stack\n");
    output(mystack);
    printf("\n");
    if (mystack->top->number == 1)
        printf("SUCCESS\n\n");
    else
        printf("FAIL\n\n");

    printf("Test2 add 3 in stack\n");
    push(mystack, 3);
    printf("Output stack\n");
    output(mystack);
    printf("\n");
    if (mystack->top->number == 3 && mystack->top->pred->number == 1)
        printf("SUCCESS\n\n");
    else
        printf("FAIL\n\n");

    printf("Test3 add 2 in stack\n");
    push(mystack, 2);
    printf("Output stack\n");
    output(mystack);
    printf("\n");
    if (mystack->top->number == 2 && mystack->top->pred->number == 3 && mystack->top->pred->pred->number == 1)
        printf("SUCCESS\n\n");
    else
        printf("FAIL\n\n");
}

void pop_tests(struct stack* mystack) {
    printf("TESTS to pop from stack\n");

    printf("Test1 pop from stack\n");
    pop(mystack);
    printf("Output stack\n");
    output(mystack);
    printf("\n");
    if (mystack->top->number == 3 && mystack->top->pred->number == 1)
        printf("SUCCESS\n\n");
    else
        printf("FAIL\n\n");

    printf("Test2 pop from stack\n");
    pop(mystack);
    printf("Output stack\n");
    output(mystack);
    printf("\n");
    if (mystack->top->number == 1)
        printf("SUCCESS\n\n");
    else
        printf("FAIL\n\n");

    printf("Test3 pop from stack\n");
    pop(mystack);
    printf("Output stack\n");
    output(mystack);
    printf("\n");
    if (mystack->top == NULL)
        printf("SUCCESS");
    else
        printf("FAIL");
}
