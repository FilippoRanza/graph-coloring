#include <stdio.h>
#include <error.h>
#include <scip/scip.h>

#include "bnp_milp/bnp_milp.h"
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

    BnPGraphColoring* bgc;
    SCIP_CALL( init_instance(&bgc, graph) );
    SCIP_CALL( enable_pricing(bgc) );

    SCIP_CALL(SCIPsolve(bgc->scip));


    SCIP_STATUS status = SCIPgetStatus(bgc->scip);
    assert(status == SCIP_STATUS_OPTIMAL);

    double sol_value = SCIPgetPrimalbound(bgc->scip);
    printf("Color count: %f\n", sol_value);

    SCIP_CALL( free_instance(bgc) );




    free_graph(graph);
    return 0;
}