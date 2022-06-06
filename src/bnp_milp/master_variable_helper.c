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

SCIP_RETCODE add_priced_variable(SCIP* scip, SCIP_VAR* var) {
    SCIP_CALL(SCIPaddPricedVar(scip, var, NEW_VAR_OBJ));
    SCIP_CALL( SCIPvarSetInitial(var, 1.0) );
    return SCIP_OKAY;
}

SCIP_RETCODE add_variable(SCIP* scip, SCIP_VAR* var, int priced) {
    if(priced) {
        SCIP_CALL(add_priced_variable(scip, var));
    } else {
        SCIP_CALL(SCIPaddVar(scip, var));
    }
    return SCIP_OKAY;
}

SCIP_RETCODE create_new_variable(SCIP* scip, SCIP_VAR** var, int* coeff, int count, int priced) {
    SCIP_CALL( SCIPcreateVarBasic(scip, var, "", NEW_VAR_MIN, NEW_VAR_MAX, NEW_VAR_OBJ, SCIP_VARTYPE_BINARY) );
    SCIP_VARDATA* vardata;
    SCIP_CALL(init_var_data(scip, &vardata, coeff, count));
    SCIPvarSetData(*var, vardata);
    SCIPvarSetDeltransData(*var, vardata_delete_function_pointer);
    SCIPvarMarkDeletable(*var);
    SCIP_CALL(  add_variable(scip, *var, priced) );

    return SCIP_OKAY;
}

SCIP_RETCODE insert_new_priced_variable(SCIP* scip, SCIP_VAR* var, SCIP_CONS** conss, int* coeff, int count) {
    while(count--) {
        SCIP_CONS* cons = *conss++;
        if(*coeff++) {
            SCIP_CALL( SCIPaddCoefSetppc(scip, cons, var) );    
        }
    }
    return SCIP_OKAY;
}
SCIP_RETCODE add_new_variable_direct(SCIP* scip, SCIP_CONS** conss, int* coeffs, int count, int priced) {
    SCIP_VAR* var;
    SCIP_CALL(create_new_variable(scip, &var, coeffs, count, priced));
    SCIP_CALL(insert_new_priced_variable(scip, var, conss, coeffs, count));
    SCIP_CALL( SCIPreleaseVar(scip, &var) );
}


SCIP_RETCODE add_new_variable(BnPGraphColoring* bgc, int* coeffs, int count) {
    SCIP_CALL( add_new_variable_direct(bgc->scip, bgc->master_cons, coeffs, count, 0) );
    return SCIP_OKAY;
}

