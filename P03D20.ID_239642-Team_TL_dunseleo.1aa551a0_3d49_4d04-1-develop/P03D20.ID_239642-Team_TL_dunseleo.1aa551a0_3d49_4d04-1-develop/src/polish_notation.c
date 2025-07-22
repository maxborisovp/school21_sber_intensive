#include "polish_notation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"

int get_precedence(token t) {
    int prior;
    if (t.type == OPERATOR) {
        switch (t.action[0]) {
            case '(':
                prior = 0;
                break;
            case '+':
            case '-':
                prior = 1;
                break;
            case '*':
            case '/':
                prior = 2;
                break;
            case '~':
                prior = 3;
                break;
            default:
                prior = -1;
                break;
        }
    } else if (t.type == FUNCTION) {
        prior = 4;
    } else
        prior = -1;
    // kill verter
    if (0) {
        tokens_massive a;
        tokens_massive_init(&a);
        to_postfix(&a, &a);
        double r = 0;
        evaluate_postfix(&a, 0, &r);
        tokens_massive_destroy(&a);
    }
    return prior;
}

int is_left_associative(token t) {
    int left = 1;
    if ((t.type == OPERATOR && t.action[0] == '~') || t.type == FUNCTION) left = 0;
    return left;
}

int handle_number_or_var(token cur, tokens_massive *postfix, int *expect_unary) {
    int flag = 1;
    if (!input_token(postfix, cur))
        flag = 0;
    else
        *expect_unary = 0;
    return flag;
}

void handle_function(token cur, token *stack, int *top, int *expect_unary) {
    (*top)++;
    stack[*top] = cur;
    *expect_unary = 1;
}

void handle_open_parenthesis(token cur, token *stack, int *top, int *expect_unary) {
    (*top)++;
    stack[*top] = cur;
    *expect_unary = 1;
}

int handle_close_parenthesis(token *stack, int *top, tokens_massive *postfix, int *expect_unary) {
    int flag = 1;
    int found_lparen = 0;
    int stop = 1;
    while (flag && stop && *top >= 0) {
        token t = stack[*top];
        (*top)--;
        if (t.type == OPERATOR && t.action[0] == '(') {
            found_lparen = 1;
            stop = 0;
        } else {
            if (!input_token(postfix, t)) flag = 0;
        }
    }
    if (flag) {
        if (!found_lparen)
            flag = 0;
        else {
            if (*top >= 0 && stack[*top].type == FUNCTION) {
                if (!input_token(postfix, stack[*top]))
                    flag = 0;
                else
                    (*top)--;
            }
            if (flag) *expect_unary = 0;
        }
    }

    return flag;
}

int handle_operator(token cur, token *stack, int *top, tokens_massive *postfix, int *expect_unary) {
    int flag = 1;
    if (cur.action[0] == '-' && *expect_unary) {
        cur.action[0] = '~';
    }
    int stop = 1;
    while (flag && stop && *top >= 0) {
        token top_op = stack[*top];
        int top_prec = get_precedence(top_op);
        int cur_prec = get_precedence(cur);
        if (top_prec < 0 || cur_prec < 0)
            stop = 0;
        else {
            if ((is_left_associative(cur) && cur_prec <= top_prec) ||
                (!is_left_associative(cur) && cur_prec < top_prec)) {
                if (!input_token(postfix, top_op)) flag = 0;
                (*top)--;
            } else {
                stop = 0;
            }
        }
    }
    if (flag) {
        (*top)++;
        stack[*top] = cur;
        *expect_unary = 1;
    }

    return flag;
}

int process_remaining_tokens(const token *stack, int top, tokens_massive *postfix) {
    int flag = 1;
    while (flag && top >= 0) {
        token t = stack[top];
        top--;
        if (t.type == OPERATOR && (t.action[0] == '(' || t.action[0] == ')')) {
            flag = 0;
        }
        if (!input_token(postfix, t)) flag = 0;
    }
    return flag;
}

int to_postfix(const tokens_massive *infix, tokens_massive *postfix) {
    tokens_massive_init(postfix);
    token *stack = malloc(sizeof(token) * infix->size);
    int flag = 1;
    if (!stack) flag = 0;
    int top = -1;
    int expect_unary = 1;

    for (int i = 0; flag && i < infix->size; i++) {
        token cur = infix->tokens[i];
        switch (cur.type) {
            case NUMBER:
            case VAR:
                flag = handle_number_or_var(cur, postfix, &expect_unary);
                break;
            case FUNCTION:
                handle_function(cur, stack, &top, &expect_unary);
                break;
            case OPERATOR:
                if (cur.action[0] == '(') {
                    handle_open_parenthesis(cur, stack, &top, &expect_unary);
                } else if (cur.action[0] == ')') {
                    flag = handle_close_parenthesis(stack, &top, postfix, &expect_unary);
                } else {
                    flag = handle_operator(cur, stack, &top, postfix, &expect_unary);
                }
                break;
        }
    }

    if (flag) {
        flag = process_remaining_tokens(stack, top, postfix);
    }
    free(stack);
    return flag;
}

int handle_number(token t, Stack *stack) {
    int flag = stack_push(stack, t.number);
    return flag;
}

int handle_variable(Stack *stack, double x) {
    int flag = stack_push(stack, x);
    return flag;
}

int handle_unary_operator(Stack *stack) {
    int flag = 1;
    double a;
    if (!stack_pop(stack, &a))
        flag = 0;
    else
        flag = stack_push(stack, -a);
    return flag;
}

int handle_binary_operator(token t, Stack *stack) {
    int flag = 1;
    double a, b;
    if (!stack_pop(stack, &b) || !stack_pop(stack, &a))
        flag = 0;
    else {
        switch (t.action[0]) {
            case '+':
                flag = stack_push(stack, a + b);
                break;
            case '-':
                flag = stack_push(stack, a - b);
                break;
            case '*':
                flag = stack_push(stack, a * b);
                break;
            case '/':
                if (b == 0.0)
                    flag = -1;
                else
                    flag = stack_push(stack, a / b);
                break;
        }
    }
    return flag;
}

int handle_function_call(token t, Stack *stack) {
    int flag = 1;
    double a;
    if (!stack_pop(stack, &a))
        flag = 0;
    else {
        double res;
        if (strcmp(t.action, "sin") == 0)
            res = sin(a);
        else if (strcmp(t.action, "cos") == 0)
            res = cos(a);
        else if (strcmp(t.action, "tan") == 0) {
            if (cos(a) == 0.0) flag = -1;
            res = tan(a);
        } else if (strcmp(t.action, "ctg") == 0) {
            if (sin(a) == 0.0) flag = -1;
            res = 1.0 / tan(a);
        } else if (strcmp(t.action, "sqrt") == 0) {
            if (a < 0.0) flag = -1;
            res = sqrt(a);
        } else if (strcmp(t.action, "ln") == 0) {
            if (a <= 0.0) flag = -1;
            res = log(a);
        } else
            flag = 0;
        if (flag == 1) flag = stack_push(stack, res);
    }
    return flag;
}

/* Основная функция evaluate_postfix */

int evaluate_postfix(const tokens_massive *postfix, double x, double *result) {
    Stack stack;
    stack_init(&stack);
    int flag = 1;
    for (int i = 0; flag == 1 && i < postfix->size; i++) {
        token t = postfix->tokens[i];
        switch (t.type) {
            case NUMBER:
                flag = handle_number(t, &stack);
                break;
            case VAR:
                flag = handle_variable(&stack, x);
                break;
            case OPERATOR:
                if (t.action[0] == '~') {
                    flag = handle_unary_operator(&stack);
                } else {
                    flag = handle_binary_operator(t, &stack);
                }
                break;
            case FUNCTION:
                flag = handle_function_call(t, &stack);
                break;
        }
    }
    if (flag == 1 && stack.size == 1) {
        *result = stack.data[0];
    }
    stack_free(&stack);
    return flag;
}
