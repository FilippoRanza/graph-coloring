#include "tokenizer.h"
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>


struct Tokens {
    size_t buff_size;
    size_t token_count;
    char** token_buff;
};
Tokens* new_tokens(size_t buff_size) {
    Tokens* tokens = malloc(sizeof(Tokens));
    if(tokens == NULL)
        return NULL;

    char** token_buff = malloc(sizeof(char*) * buff_size);
    if(token_buff == NULL) {
        free(tokens);
        return NULL;
    }

    tokens->buff_size = buff_size;
    tokens->token_count = 0;
    tokens->token_buff = token_buff;
    return tokens;
}

TokenizerResult tokenize(Tokens* tokens, char* buff) {

    char** curr_token = tokens->token_buff;
    tokens->token_count = 0;
    int prev = -1;
    char c;
    while((c = *buff)) {
        if(isspace(c)) {
            if(!isspace(prev))
                *buff = '\0';
        } else {
            if(prev == -1 || (isspace(prev))) {
                *curr_token++ =  buff;
                if(++tokens->token_count == tokens->buff_size) {
                    return BuffOut;
                }
            }
        }

        prev = c;
        buff++;
    }

    return Ok;
}

size_t tokens_count(Tokens* t) {
    return t->token_count;
}

char** tokens_buff(Tokens* t) {
    return t->token_buff;
}

void free_tokens(Tokens* t) {
    free(t->token_buff);
    free(t);
}

// TokenizerResult tokenize(char* buff, char** token_buff, size_t tokens) {

//     return Ok;
// }