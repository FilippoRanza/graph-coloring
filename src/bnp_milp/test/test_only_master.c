
#include <assert.h>
#include <stdio.h>

#include <scip/scip.h>

#include <bnp_milp/bnp_milp.h>
#include <simple_dimacs/simple_dimacs.h>

int main(int argc, char** argv) {

    assert(argc == 2);

    Graph* graph = read_file_graph(argv[1]);
    assert(graph != NULL);

    BnPGraphColoring* bgc;
    SCIP_CALL( init_instance(&bgc, graph) );

    SCIP_CALL(SCIPsolve(bgc->scip));


    SCIP_STATUS status = SCIPgetStatus(bgc->scip);
    assert(status == SCIP_STATUS_OPTIMAL);

    double sol_value = SCIPgetPrimalbound(bgc->scip);
    assert(sol_value == 5);


    SCIP_CALL( free_instance(bgc) );



    free_graph(graph);
    return 0;
}








