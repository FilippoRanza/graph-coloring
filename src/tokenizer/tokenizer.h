#include <stddef.h>

#ifndef __TOKENIZE_H
#define __TOKENIZE_H


typedef enum {
    Ok,
    BuffOut
} TokenizerResult;


typedef struct Tokens Tokens;

Tokens* new_tokens(size_t buff_size);
TokenizerResult tokenize(Tokens* tokens, char* buff);
size_t tokens_count(Tokens*);
char** tokens_buff(Tokens*);
void free_tokens(Tokens*);

#endif