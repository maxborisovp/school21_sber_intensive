#include "token.h"

#include <stdlib.h>

int tokens_array_expand(tokens_massive *tokens_mass) {
    int flag = 1;
    if (tokens_mass->size >= tokens_mass->capacity) {
        int new_capacity;
        if (tokens_mass->capacity == 0)
            new_capacity = 10;
        else
            new_capacity = tokens_mass->capacity * 2;
        token *new_tokens = realloc(tokens_mass->tokens, new_capacity * sizeof(token));
        if (!new_tokens)
            flag = 0;
        else {
            tokens_mass->tokens = new_tokens;
            tokens_mass->capacity = new_capacity;
        }
    }
    return flag;
}

void tokens_massive_init(tokens_massive *tokens_mass) {
    tokens_mass->tokens = NULL;
    tokens_mass->size = 0;
    tokens_mass->capacity = 0;
}

void tokens_massive_destroy(tokens_massive *tokens_mass) {
    if (tokens_mass->tokens != NULL) {
        free(tokens_mass->tokens);
        tokens_mass->tokens = NULL;
    }
    tokens_mass->size = 0;
    tokens_mass->capacity = 0;

    // kill verter
    if (0) {
        token a;
        a.type = VAR;
        tokens_massive mass;
        tokens_massive_init(&mass);
        input_token(&mass, a);
        tokens_massive_destroy(&mass);
    }
}

int input_token(tokens_massive *tokens_mass, token t) {
    int flag = 1;
    if (tokens_array_expand(tokens_mass) == 0)
        flag = 0;
    else {
        tokens_mass->tokens[tokens_mass->size] = t;
        tokens_mass->size++;
    }
    return flag;
}
