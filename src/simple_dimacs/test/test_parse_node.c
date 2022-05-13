#include <dimacs_parser.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int main() {

    Parser* parser = new_parser();
    assert(parser != NULL);

    char* buff = malloc(100);

    int values[] =  {-123, 0, 560};


    for(int i = 0; i < 3; i++) {
        int v = values[i];
        sprintf(buff, "n 102 %d", v);
        ParseResult result = parse_line(parser, buff);
        assert(result == ParseOk);

        EntryType type = get_entry_type(parser);
        assert(type == Node);

        NodeData* data = get_node_data(parser);
        assert(data->node_id == 102);
        assert(data->weight == v);

    }



    free(buff);
    free_parser(parser);
    return 0;
}