#include "bnp_milp.h"


SCIP_RETCODE init_instance(BnPGraphColoring** bgcp, Graph* g) {
    BnPGraphColoring* bgc = malloc(sizeof(BnPGraphColoring));
    if(bgc == NULL)
        return SCIP_NOMEMORY;
    
    bgc->graph = g;
    bgc->scip = NULL;
    bgc->master_cons = NULL;
    
    SCIP_CALL(create_bnp_master(bgc));


    *bgcp = bgc;
    return SCIP_OKAY;
}

SCIP_RETCODE free_instance(BnPGraphColoring* bgc) {
    int node_count = bgc->graph->node_count;
    SCIP_CONS** conss = bgc->master_cons;
    while(node_count--) {
        SCIP_CALL(SCIPreleaseCons(bgc->scip, conss++));
    }
    SCIP_CALL(SCIPfree(&bgc->scip));
    free(bgc);
    return SCIP_OKAY;
}
