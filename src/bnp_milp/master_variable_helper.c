#include "bnp_milp.h"
#include <scip/cons_setppc.h>

#define NEW_VAR_MIN 0.0
#define NEW_VAR_MAX 1.0
#define NEW_VAR_OBJ 1.0


SCIP_RETCODE init_var_data(SCIP* scip, SCIP_VARDATA** vardata, int* coeff, int count) {

    SCIP_CALL( SCIPallocBlockMemory(scip, vardata));
    (*vardata)->coeff = coeff;
    (*vardata)->count = count; 

    return SCIP_OKAY;
}

SCIP_RETCODE free_var_data(SCIP* scip, SCIP_VARDATA** vardata) {
    SCIPfreeBlockMemoryArray(scip, &(*vardata)->coeff, (*vardata)->count);
    SCIPfreeBlockMemory(scip, vardata);
    return SCIP_OKAY;
}

static SCIP_DECL_VARDELTRANS(vardata_delete_function_pointer) {

    SCIP_CALL( free_var_data(scip, vardata) );
    return SCIP_OKAY;
}
#include <stdio.h>

SCIP_RETCODE add_variable(SCIP* scip, SCIP_VAR* var) {
    SCIP_STATUS status = SCIPgetStatus(scip);
    if(status == SCIP_STAGE_SOLVING) {
        SCIP_CALL(SCIPaddPricedVar(scip, var, NEW_VAR_OBJ));
    } else {
        SCIP_CALL(SCIPaddVar(scip, var));
    }
    return SCIP_OKAY;
}

SCIP_RETCODE create_new_variable(SCIP* scip, SCIP_VAR** var, int* coeff, int count) {
    SCIP_CALL( SCIPcreateVarBasic(scip, var, "", NEW_VAR_MIN, NEW_VAR_MAX, NEW_VAR_OBJ, SCIP_VARTYPE_BINARY) );
    SCIP_VARDATA* vardata;
    SCIP_CALL(init_var_data(scip, &vardata, coeff, count));
    SCIPvarSetData(*var, vardata);
    SCIPvarSetDeltransData(*var, vardata_delete_function_pointer);
    SCIPvarMarkDeletable(*var);
    SCIP_CALL(  add_variable(scip, *var) );
    SCIP_CALL( SCIPchgVarUbLazy(scip, *var, NEW_VAR_MAX) );

    return SCIP_OKAY;
}

SCIP_RETCODE insert_new_priced_variable(SCIP* scip, SCIP_VAR* var, SCIP_CONS** conss, int* coeff, int count) {
    while(count--) {
        if(*coeff++) {
            SCIP_CALL( SCIPaddCoefSetppc(scip, *conss++, var) );    
        }
    }


    return SCIP_OKAY;
}

SCIP_RETCODE add_new_variable(BnPGraphColoring* bgp, int* coeffs, int count) {
    SCIP_VAR* var;
    SCIP_CALL(create_new_variable(bgp->scip, &var, coeffs, count));
    SCIP_CALL(insert_new_priced_variable(bgp->scip, var, bgp->master_cons, coeffs, count));
    SCIP_CALL( SCIPreleaseVar(bgp->scip, &var) );
    return SCIP_OKAY;
}

