#include <assert.h>
#include <stdio.h>

#include <base_milp/milp.h>
#include <simple_dimacs/simple_dimacs.h>

#include <scip/scip.h>



int main(int argc, char** argv) {

    fprintf(stderr, "Remember: pass graph's file name as cli argument\n");
    assert(argc == 2);

    fprintf(stderr, "Reading graph...");
    Graph* graph = read_file_graph(argv[1]);
    assert(graph != NULL);
    fprintf(stderr, "Done\n");

    Instance* instance = new_instance(graph, 4);
    assert(instance != NULL);
    
    SCIP_CALL( SCIPsolve(instance->scip_env) );

    SCIP_STATUS status = SCIPgetStatus(instance->scip_env);
    assert(status == SCIP_STATUS_OPTIMAL);

    double sol_value = SCIPgetPrimalbound(instance->scip_env);
    fprintf(stderr, "ACTUAL %f\n", sol_value);

    SCIP_SOL* sol = SCIPgetBestSol(instance->scip_env);
    for(size_t n = 0; n < instance->node_count; n++) {
        for(size_t c = 0; c < instance->color_count; c++) {
            double val = SCIPgetSolVal(instance->scip_env, sol, instance->color_selection[n][c]);
            fprintf(stderr, "X[%ld, %ld] = %f", n, c, val);
        }
        fprintf(stderr, "\n");
    }


    assert(sol_value == 2.0);

    free_instance(instance);
    return 0;
} 