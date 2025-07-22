#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_number(const char **p, tokens_massive *tokens_mass) {
    int flag = 1;
    char *end_chisla;
    double value = strtod(*p, &end_chisla);
    if (end_chisla == *p)
        flag = 0;
    else {
        token t;
        t.type = NUMBER;
        t.number = value;
        if (!input_token(tokens_mass, t))
            flag = 0;
        else
            *p = end_chisla;
    }
    return flag;
}

int parse_variable(const char **p, tokens_massive *tokens_mass) {
    int flag = 1;
    token t;
    t.type = VAR;

    if (!input_token(tokens_mass, t))
        flag = 0;
    else
        (*p)++;
    return flag;
}

int parse_operator(const char **p, tokens_massive *tokens_mass) {
    int flag = 1;
    token t;
    t.type = OPERATOR;
    switch (**p) {
        case '+':
            strcpy(t.action, "+");
            break;
        case '-':
            strcpy(t.action, "-");
            break;
        case '*':
            strcpy(t.action, "*");
            break;
        case '/':
            strcpy(t.action, "/");
            break;
        case '(':
            strcpy(t.action, "(");
            break;
        case ')':
            strcpy(t.action, ")");
            break;
    }

    if (!input_token(tokens_mass, t))
        flag = 0;
    else
        (*p)++;
    return flag;
}

int parse_function(const char **p, tokens_massive *tokens_mass) {
    int flag = 1;
    int len = 0;
    while ((*p)[len] >= 'a' && (*p)[len] <= 'z') {
        len++;
    }

    token t;
    t.type = FUNCTION;
    if (len == 3 && strncmp(*p, "sin", 3) == 0)
        strcpy(t.action, "sin");
    else if (len == 3 && strncmp(*p, "cos", 3) == 0)
        strcpy(t.action, "cos");
    else if (len == 3 && strncmp(*p, "tan", 3) == 0)
        strcpy(t.action, "tan");
    else if (len == 3 && strncmp(*p, "ctg", 3) == 0)
        strcpy(t.action, "ctg");
    else if (len == 4 && strncmp(*p, "sqrt", 4) == 0)
        strcpy(t.action, "sqrt");
    else if (len == 2 && strncmp(*p, "ln", 2) == 0)
        strcpy(t.action, "ln");
    else
        flag = 0;
    if (flag == 1) {
        if (!input_token(tokens_mass, t))
            flag = 0;
        else
            *p += len;
    }
    return flag;
}

int parsing(const char *expr, tokens_massive *tokens_mass) {
    tokens_massive_init(tokens_mass);
    const char *p = expr;
    int flag = 1;
    while (flag == 1 && *p != '\0') {
        if (*p == ' ') {
            p++;
        } else if (((*p) >= '0' && (*p) <= '9') || (*p == '.' && (*(p + 1) >= '0' && *(p + 1) <= '9'))) {
            flag = parse_number(&p, tokens_mass);
        } else if (*p == 'x') {
            flag = parse_variable(&p, tokens_mass);
        } else if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')') {
            flag = parse_operator(&p, tokens_mass);
        } else if (*p >= 'a' && *p <= 'z') {
            flag = parse_function(&p, tokens_mass);
        } else
            flag = 0;
    }
    if (flag) flag = check_vars(tokens_mass);
    // kill verter
    if (0) {
        tokens_massive mass;
        tokens_massive_init(&mass);
        parsing("", &mass);
        tokens_massive_destroy(&mass);
    }
    return flag;
}

int check_vars(const tokens_massive *tokens_mass) {
    int flag = 1;
    for (int i = 0; i < tokens_mass->size; i++) {
        if ((tokens_mass->tokens[i].type == VAR || tokens_mass->tokens[i].type == NUMBER) &&
            tokens_mass->size > 1) {
            if (i > 0 && tokens_mass->tokens[i - 1].type != OPERATOR) flag = 0;
            if (i < tokens_mass->size - 1 && tokens_mass->tokens[i + 1].type != OPERATOR) flag = 0;
        }
        if (strcmp(tokens_mass->tokens[i].action, ")") == 0 && tokens_mass->tokens[i].type == OPERATOR &&
            strcmp(tokens_mass->tokens[i - 1].action, "(") == 0 &&
            tokens_mass->tokens[i - 1].type == OPERATOR)
            flag = 0;
    }
    return flag;
}
