#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <tokenizer.h>
#include "simple_dimacs.h"
#include "dimacs_parser.h"

#define BUFF_SIZE 4096
#define TRUE 1
#define FALSE 0

void free_graph(Graph* g) {
    free(g->arcs);
    free(g);
}

Graph* allocate_graph(size_t node_count, size_t arc_count) {
    Graph* g = malloc(sizeof(Graph));
    if(g == NULL) 
        return NULL;

    
    Arc* arcs = malloc(sizeof(Arc) * arc_count);
    if(arcs == NULL) {
        free(g);
        return NULL;
    }
    
    g->node_count = node_count;
    g->arcs_count = arc_count;
    g->arcs = arcs;

    return g;
}

typedef enum {
    ok,
    end,
    buff_out
} result;

result read_line(FILE* fp, char* buff, size_t buff_size) {

    char* tmp = buff;
    char c;
    while((c = fgetc(fp)) && c != EOF && c != '\n' && buff_size--)
        *tmp++ = c;
    
    *tmp = '\0';

    result output;
    if(c == EOF)
        output = (tmp - buff) ? ok : end;
    else
        output = buff_size ? ok : buff_out;

    return output;
}

Graph* make_graph(ProblemData* data) {
    return allocate_graph(data->node_count, data->edge_count);
}

void add_edge(Graph* graph, EdgeData* data, size_t arc_index) {
    graph->arcs[arc_index].src = data->src - 1;
    graph->arcs[arc_index].dst = data->dst - 1;
}

Graph* read_graph(FILE* fp) {
    char* buff = malloc(BUFF_SIZE);
    if(buff == NULL)
        return NULL;

    Parser* parser = new_parser();
    if(parser == NULL) {
        free(buff);
        return NULL;
    }
    Graph* g = NULL;
    result res;
    int run = TRUE;
    size_t arc_index = 0;
    ParseResult parse_res;
    while((res = read_line(fp, buff, BUFF_SIZE)) != end && run) {
        parse_res = parse_line(parser, buff);
        if(parse_res != ParseOk)
            break;
        EntryType type = get_entry_type(parser);
        switch(type) {
            case Comment:
                break;
            case Edge:
                add_edge(g, get_edge_data(parser), arc_index++);
                break;
            case Node:
                break;
            case Problem:
                g = make_graph(get_problem_data(parser));
                if(g == NULL)
                    run = FALSE;
                break;
        }
    }

    free(buff);
    free_parser(parser);
    if(parse_res != ParseOk) {
        free_graph(g);
        g = NULL;
    }
    return g;
}


Graph* read_file_graph(char* filename) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) 
        return NULL;

    Graph* g = read_graph(fp);
    fclose(fp);

    return g;
}



