#ifndef TOKEN_H
#define TOKEN_H

typedef enum { NUMBER, VAR, OPERATOR, FUNCTION } token_type;

typedef struct {
    token_type type;
    union {
        double number;
        char action[5];
    };
} token;

typedef struct {
    token *tokens;
    int size;
    int capacity;
} tokens_massive;

int tokens_array_expand(tokens_massive *tokens_mass);
void tokens_massive_init(tokens_massive *tokens_mass);
void tokens_massive_destroy(tokens_massive *tokens_mass);
int input_token(tokens_massive *tokens_mass, token t);

#endif
