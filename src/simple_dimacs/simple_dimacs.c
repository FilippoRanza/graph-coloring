#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "simple_dimacs.h"



void free_graph(graph* g) {
    free(g->arcs);
    free(g);
}

graph* allocate_graph(size_t node_count, size_t arc_count) {
    graph* g = malloc(sizeof(graph));
    if(g == NULL) 
        return NULL;

    
    arc* arcs = malloc(sizeof(arc) * arc_count);
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

    char c;
    while((c = fgetc(fp)) && c != EOF && c != '\n' && buff_size--)
        *buff++ = c;
    
    *buff = '\0';

    result output;
    if(c == EOF)
        output = end;
    else if(c == '\n')
        output = buff_size ? ok : buff_out;

    return output;
}


typedef enum{
    comment,
    problem, 
    nodes,
    edge
} linetype;

graph* read_graph(FILE* fp) {

}


graph* read_file_graph(char* filename) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) 
        return NULL;

    graph* g = read_graph(fp);
    fclose(fp);

    return g;
}



