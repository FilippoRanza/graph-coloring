
#include "bnp_milp.h"


SCIP_RETCODE init_scip(SCIP** scip) {
    SCIP_CALL( SCIPcreate(scip) );
    SCIP_CALL( SCIPincludeDefaultPlugins(*scip) );
    SCIP_CALL( SCIPincludePricerGraphColoring(*scip) );
    SCIP_CALL( SCIPsetIntParam(*scip,"presolving/maxrestarts",0) );
    SCIP_CALL( SCIPsetSeparating(*scip, SCIP_PARAMSETTING_OFF, TRUE) );
    SCIP_CALL( SCIPcreateProbBasic(*scip, "Graph-Coloring"));
    SCIP_CALL( SCIPsetObjsense(*scip, SCIP_OBJSENSE_MINIMIZE) );
    return SCIP_OKAY;
}

SCIP_RETCODE init_constr(SCIP* scip, SCIP_CONS** constr) {

    SCIP_CALL(SCIPcreateConsSetpart(scip, constr, "", 0, NULL, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE));
    SCIP_CALL(SCIPaddCons(scip, *constr));
    return SCIP_OKAY;
}

SCIP_RETCODE init_constrs(SCIP* scip, SCIP_CONS*** constr, int node_count) {

    SCIP_CONS** cons_buff;
    SCIP_CALL(SCIPallocBlockMemoryArray(scip, &cons_buff, node_count));
    SCIP_CONS** tmp_buff = cons_buff;

    for(int i = 0; i < node_count; i++) {
        SCIP_CALL(init_constr(scip, tmp_buff++));
    }


    *constr = cons_buff;
    return SCIP_OKAY;
}
 
SCIP_RETCODE create_bnp_master(BnPGraphColoring* bgc) {
    SCIP** scip = &bgc->scip;
    SCIP_CONS*** constr = &bgc->master_cons;
    int node_count = bgc->graph->node_count;
    SCIP_CALL( init_scip(scip) );    
    SCIP_CALL( init_constrs(*scip, constr, node_count));  
    SCIP_CALL(create_basic_patterns(bgc));

    return SCIP_OKAY;
}


