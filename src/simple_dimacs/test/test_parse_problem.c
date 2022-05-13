
#include <dimacs_parser.h>
#include <assert.h>

#include "test_utils.h"


int main() {

    Parser* parser = new_parser();
    assert(parser != NULL);

    char* line = make_modifiable_string("p edge 100 431");
    ParseResult result = parse_line(parser, line);
    assert(result == ParseOk);

    EntryType type = get_entry_type(parser);
    assert(type == Problem);

    ProblemData* data = get_problem_data(parser);
    assert(data->node_count == 100);
    assert(data->edge_count == 431);


    free_parser(parser);
    return 0;
}