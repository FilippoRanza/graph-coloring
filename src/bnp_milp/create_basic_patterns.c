#include "bnp_milp.h"

SCIP_RETCODE create_basic_pattern(BnPGraphColoring* bgp, int node_id, int node_count) {
    int* buff;
    SCIP_CALL(SCIPallocBlockMemoryArray(bgp->scip, &buff, node_count));
    for(int i = 0; i < node_count; i++) {
        *buff = 0;
    }
    buff[node_id] = 1;
    add_new_variable(bgp, buff, node_count);
    return SCIP_OKAY;
}


SCIP_RETCODE create_basic_patterns(BnPGraphColoring* bgp) {
    int node_count = bgp->graph->node_count;
    for(int i = 0; i < node_count; i++) {
        create_basic_pattern(bgp, i, node_count);
    }
    return SCIP_OKAY;
}
