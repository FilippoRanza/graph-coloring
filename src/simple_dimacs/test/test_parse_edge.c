#include <dimacs_parser.h>
#include <assert.h>

#include "test_utils.h"


int main() {

    Parser* parser = new_parser();
    assert(parser != NULL);

    char* line = make_modifiable_string("e 23 54");
    ParseResult result = parse_line(parser, line);
    assert(result == ParseOk);

    EntryType type = get_entry_type(parser);
    assert(type == Edge);

    EdgeData* data = get_edge_data(parser);
    assert(data->src == 23);
    assert(data->dst == 54);


    free_parser(parser);
    return 0;
}