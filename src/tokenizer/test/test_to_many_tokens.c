#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../tokenizer.h"

#include "test_utils.h"

int main() {

    Tokens* tokens = new_tokens(10);
    assert(tokens != NULL);

    char* str = make_modifiable_string("A B C D E F G H I L M N O P");

    TokenizerResult result = tokenize(tokens, str);
    assert(result == BuffOut);

    assert(tokens_count(tokens) == 10);

    char** actual = tokens_buff(tokens);
    char* expected[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "L M N O P"};
    for(int i = 0; i < 10; i++) {
        fprintf(stderr, "%s - %s\n", actual[i], expected[i]);
        assert(strcmp(actual[i], expected[i]) == 0);
    }

    free_tokens(tokens);

    return 0;
}