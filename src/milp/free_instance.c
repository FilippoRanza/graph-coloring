#include "milp.h"


void free_constr_if_set(SCIP* scip, SCIP_CONS* cons) {
    if (scip != NULL && cons != NULL) 
        SCIPreleaseCons(scip, &cons);
}

void free_constr_vector_if_set(SCIP* scip, SCIP_CONS** cons, size_t count) {
    SCIP_CONS** tmp_ptr = cons;
    while(count--) {
        SCIP_CONS* curr = *tmp_ptr++;
        if(curr != NULL)
            free_constr_if_set(scip, curr);
    }
    free(cons);
}

void free_var_if_set(SCIP* scip, SCIP_VAR** var) {
    if(var == NULL)
        return;
    SCIPreleaseVar(scip, var);
    
}

void free_vars_if_set(SCIP* scip, SCIP_VAR** vars, size_t count) {
    if(scip == NULL)
        return;

    SCIP_VAR** tmp_ptr = vars;
    while(count--)
        free_var_if_set(scip, tmp_ptr++);

    free(vars);
}

void free_vars_matrix_if_set(SCIP* scip, SCIP_VAR*** vars, size_t columns, size_t rows) {
    SCIP_VAR*** tmp_ptr = vars;
    while(columns--) {
        SCIP_VAR** curr = *tmp_ptr++;
        if(curr != NULL)
            free_vars_if_set(scip, curr, rows);
    }
    free(vars);
}



void free_scip_instance_if_set(Instance* instance) {

    if(instance->scip_env == NULL)
        return;
    
    
    // free constraints
    free_constr_if_set(instance->scip_env, instance->one_color);

    size_t not_same_color_constrs = instance->color_count * instance->graph->arcs_count;
    free_constr_vector_if_set(instance->scip_env, instance->not_same_color, not_same_color_constrs);

    size_t enable_color_constrs = instance->color_count * instance->node_count;
    free_constr_vector_if_set(instance->scip_env, instance->enable_color, enable_color_constrs);
    
    // free variables
    free_vars_matrix_if_set(instance->scip_env, instance->color_selection, instance->node_count, instance->color_count);
    free_vars_if_set(instance->scip_env, instance->color_enable, instance->color_count);


    SCIPfree(&instance->scip_env);
}

void free_instance(Instance* instance) {
    if(instance == NULL)
        return;

    free_scip_instance_if_set(instance);
    free_graph(instance->graph);
    
    free(instance);
}
