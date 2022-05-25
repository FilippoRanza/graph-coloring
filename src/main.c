#include <stdio.h>
#include <error.h>

#include "base_milp/milp.h"
#include "simple_dimacs/simple_dimacs.h"

int main(int argc, char** argv) {
    
    Graph* graph;
    if(argc == 1)
        graph = read_graph(stdin);
    else
        graph = read_file_graph(argv[1]);

    if(graph == NULL) {
        perror(argv[0]);
        fprintf(stderr, "Impossible to read graph\nAbort\n");
        abort();
    }

    Instance* instance = new_instance(graph, 100);
    if(instance == NULL) {
        perror(argv[0]);
        fprintf(stderr, "Impossible to build instance\nAbort\n");
        free_graph(graph);
        abort();
    }

    SCIP_CALL( SCIPsolve(instance->scip_env) );

    SCIP_STATUS status = SCIPgetStatus(instance->scip_env);
    assert(status == SCIP_STATUS_OPTIMAL);

    double sol_value = SCIPgetPrimalbound(instance->scip_env);
    fprintf(stderr, "ACTUAL %f\n", sol_value);


    free_instance(instance);
    return 0;
}