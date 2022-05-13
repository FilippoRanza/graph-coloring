#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../tokenizer.h"
#include "test_utils.h"



int main() {

    Tokens* tokens = new_tokens(10);
    assert(tokens != NULL);

    char* str = make_modifiable_string("   ABC   DEF GHI LMNO  ");
    assert(str != NULL);
    TokenizerResult result = tokenize(tokens, str);
    assert(result == Ok);

    fprintf(stderr, "Actual token count %d\n", tokens_count(tokens));
    assert(tokens_count(tokens) == 4);
    char** actual = tokens_buff(tokens);
    char* expected[] = {
        "ABC", "DEF", "GHI", "LMNO"
    };
    
    for(int i = 0; i < 4; i++) {
        assert(strcmp(expected[i], actual[i]) == 0);
    }

    free_tokens(tokens);

    return 0;
}