#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <simple_dimacs.h>


void assert_arc(Arc* arc, int idx, int src, int dst) {
    fprintf(stderr, "ARC: %d\n", idx);
    fprintf(stderr, "SOURCE:\n");
    fprintf(stderr, "\tA: %ld\n", arc[idx].src);
    fprintf(stderr, "\tE: %d\n", src);
    assert(arc[idx].src == src);

    fprintf(stderr, "DESTINATION:\n");
    fprintf(stderr, "\tA: %ld\n", arc[idx].dst);
    fprintf(stderr, "\tE: %d\n", dst);
    assert(arc[idx].dst == dst);
    fprintf(stderr, "\n\n");

}

int main(int argc, char** argv) {

    assert(argc == 2);
    char* file_name = argv[1];


    Graph* graph = read_file_graph(file_name);
    assert(graph != NULL);


    assert(graph->node_count == 5);
    assert(graph->arcs_count == 6);

    Arc* arcs = graph->arcs;
    assert_arc(arcs, 0, 0, 3);
    assert_arc(arcs, 1, 0, 2);
    assert_arc(arcs, 2, 1, 3);
    assert_arc(arcs, 3, 1, 2);
    assert_arc(arcs, 4, 2, 4);
    assert_arc(arcs, 5, 3, 4);

    free_graph(graph);
    return 0;

}