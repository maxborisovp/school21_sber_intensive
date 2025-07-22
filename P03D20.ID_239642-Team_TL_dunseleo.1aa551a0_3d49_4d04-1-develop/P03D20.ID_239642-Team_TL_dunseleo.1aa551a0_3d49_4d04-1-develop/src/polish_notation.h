#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H
#include "stack.h"
#include "token.h"
int get_precedence(token t);
int is_left_associative(token t);
int handle_number_or_var(token cur, tokens_massive *postfix, int *expect_unary);
void handle_function(token cur, token *stack, int *top, int *expect_unary);
void handle_open_parenthesis(token cur, token *stack, int *top, int *expect_unary);
int handle_close_parenthesis(token *stack, int *top, tokens_massive *postfix, int *expect_unary);
int handle_operator(token cur, token *stack, int *top, tokens_massive *postfix, int *expect_unary);
int process_remaining_tokens(const token *stack, int top, tokens_massive *postfix);
int handle_number(token t, Stack *stack);
int handle_variable(Stack *stack, double x);
int handle_unary_operator(Stack *stack);
int handle_binary_operator(token t, Stack *stack);
int handle_function_call(token t, Stack *stack);

int to_postfix(const tokens_massive *infix, tokens_massive *postfix);
int evaluate_postfix(const tokens_massive *postfix, double x, double *result);
#endif
