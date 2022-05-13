#include <dimacs_parser.h>
#include <assert.h>
#include "test_utils.h"


int main() {
    Parser* parser = new_parser();
    assert(parser != NULL);

    char* line = make_modifiable_string("c Hello Comment Stuff... 42");
    ParseResult result = parse_line(parser, line);
    assert(result == ParseOk);

    EntryType type = get_entry_type(parser);
    assert(type == Comment);

    free_parser(parser);
    return 0;
}