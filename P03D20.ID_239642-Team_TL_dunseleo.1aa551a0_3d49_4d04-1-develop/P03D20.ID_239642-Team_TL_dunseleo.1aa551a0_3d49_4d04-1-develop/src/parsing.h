#ifndef PARSING_H
#define PARSING_H
#include "token.h"
int parse_number(const char **p, tokens_massive *tokens_mass);
int parse_variable(const char **p, tokens_massive *tokens_mass);
int parse_operator(const char **p, tokens_massive *tokens_mass);
int parse_function(const char **p, tokens_massive *tokens_mass);
int parsing(const char *expr, tokens_massive *tokens_mass);
int check_vars(const tokens_massive *tokens_mass);
#endif
