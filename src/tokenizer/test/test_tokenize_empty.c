#include <assert.h>
#include "../tokenizer.h"


int main() {

    Tokens* tokens = new_tokens(10);
    assert(tokens != NULL);

    TokenizerResult result = tokenize(tokens, "");
    assert(result == Ok);

    assert(tokens_count(tokens) == 0);

    free_tokens(tokens);

    return 0;
}