#include<stdint.h>
#include<stdio.h>



typedef struct  {
    size_t src;
    size_t dst;
} Arc;


typedef struct {
    size_t node_count;
    size_t arcs_count;
    Arc* arcs;
} Graph;





void free_graph(Graph* g);
Graph* read_graph(FILE* fp);
Graph* read_file_graph(char* filename);

