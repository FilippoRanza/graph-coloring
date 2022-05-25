#include <assert.h>
#include <stdio.h>

#include <base_milp/milp.h>
#include <simple_dimacs/simple_dimacs.h>




int main(int argc, char** argv) {

    fprintf(stderr, "Remember: pass graph's file name as cli argument\n");
    assert(argc == 2);

    fprintf(stderr, "Reading graph...");
    Graph* graph = read_file_graph(argv[1]);
    assert(graph != NULL);
    fprintf(stderr, "Done\n");

    Instance* instance = new_instance(graph, 10);
    assert(instance != NULL);
    


    free_instance(instance);

    return 0;
} 
