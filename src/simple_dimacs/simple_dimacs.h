#include<stdint.h>



typedef struct  {
    size_t src;
    size_t dst;
} arc;


typedef struct {
    size_t node_count;
    size_t arcs_count;
    arc* arcs;
} graph;





void free_graph(graph* g);
graph* read_graph(FILE* fp);
graph* read_file_graph(char* filename);

