#include "milp.h"



/*
    Arc-color association variable is 
    organized in a linear vector and
    not in a matrix.
    This vector is organized by "color major". 
    So given N nodes and M colors the first
    M values in the vector are the possible 
    associaton Node 1 - colors. Set second
    set of M variables are the color association
    relative to the secon node and so on.
*/

size_t get_node_initial_position(size_t color_count, size_t node) {
    return color_count * node;
}

size_t get_variable_index(size_t color_count, size_t node, size_t color) {
    return  get_node_initial_position(color_count, node) + color;
}


SCIP_RETCODE init_scip_env(SCIP** scip) {
    SCIP_CALL( SCIPcreate(scip) );
    SCIP_CALL( SCIPincludeDefaultPlugins(*scip) );
    SCIP_CALL( SCIPcreateProbBasic(*scip, "Graph-Coloring"));
    SCIP_CALL( SCIPsetObjsense(*scip, SCIP_OBJSENSE_MAXIMIZE) );
    return SCIP_OKAY;
}

SCIP_RETCODE add_bin_variable(SCIP* scip, SCIP_VAR*** vars, size_t count, double obj_coeff) {
    SCIP_VAR** var_buff = malloc(sizeof(SCIP_VAR*) * count);
    if(var_buff == NULL)
        return SCIP_NOMEMORY;

    SCIP_VAR** tmp_ptr = var_buff;
    for(size_t i = 0; i < count; i++)  {
        SCIP_VAR* var = NULL;
        SCIPcreateVarBasic(scip, &var, "", 0.0, 1.0, obj_coeff, SCIP_VARTYPE_BINARY);
        SCIP_CALL( SCIPaddVar(scip, var));
        *tmp_ptr++ = var;
    }
    *vars = var_buff;
    return SCIP_OKAY;
}

SCIP_RETCODE add_bin_matrix(SCIP* scip, SCIP_VAR**** vars, size_t columns, size_t rows, double obj_coeff) {
    SCIP_VAR*** var_buff = malloc(sizeof(SCIP**) * columns);
    if(var_buff == NULL)
        return SCIP_NOMEMORY;
    SCIP_VAR*** tmp_ptr = var_buff;

    while(columns--) {
        SCIP_VAR** curr = NULL;
        add_bin_variable(scip, &curr, rows, obj_coeff);
        *tmp_ptr++ = curr;
    }
    *vars = var_buff;
    return SCIP_OKAY;
}

SCIP_RETCODE add_one_color_per_node(SCIP* scip, SCIP_CONS** cons, SCIP_VAR*** vars, size_t colors, size_t nodes) {
    SCIP_CALL(SCIPcreateConsBasicOrbitope(scip, cons, "", vars, SCIP_ORBITOPETYPE_PARTITIONING, nodes, colors, FALSE, FALSE, TRUE, FALSE)); 
    return SCIP_OKAY;
}

// SCIP_RETCODE add_not_same_color(SCIP* scip, SCIP_VAR*** vars, SCIP_CONS*** cons, Arc* arc, size_t colors) {
//     SCIP_CONS** cons_buff = malloc(sizeof(SCIP_CONS**) * colors);
//     if(cons_buff == NULL)
//         return SCIP_NOMEMORY;

//     SCIP_CONS** tmp_ptr = cons_buff;
//     for(size_t i = 0; i < colors; i++) {
//         SCIP_CONS* curr = NULL;

//     }

//     *cons = cons_buff;
//     return SCIP_OKAY;
// }

SCIP_RETCODE add_all_not_same_color(SCIP* scip, SCIP_VAR*** vars, SCIP_CONS*** cons, Arc* arcs, size_t arc_count, size_t colors) {
    SCIP_CONS** cons_buff= malloc(sizeof(SCIP_CONS*) * (arc_count * colors));
    if(cons_buff == NULL)
        return SCIP_NOMEMORY;

    SCIP_CONS** tmp_ptr = cons_buff;
    while(arc_count--) {
        Arc* arc = arcs++;


        SCIP_VAR** src_col = vars[arc->src];
        SCIP_VAR** dst_col = vars[arc->dst];
        for(size_t i = 0; i < colors; i++) {
            SCIP_CONS* curr = NULL;
            SCIP_CALL(SCIPcreateConsBasicKnapsack(scip, &curr, "", 0, NULL, NULL, 1));
            SCIP_CALL( SCIPaddCoefKnapsack(scip, curr, *src_col++, 1) );
            SCIP_CALL( SCIPaddCoefKnapsack(scip, curr, *dst_col++, 1) );
            *tmp_ptr++ = curr;
        }
    }

    *cons = cons_buff;
    return SCIP_OKAY;
}

SCIP_RETCODE add_enable_color(SCIP* scip, SCIP_VAR*** set_color, SCIP_VAR** enable_color, SCIP_CONS*** cons, size_t nodes, size_t colors) {
    size_t constr_count = nodes * colors;
    SCIP_CONS** cons_buff = malloc(sizeof(SCIP_CONS*) * constr_count);
    if(cons_buff == NULL)
        return SCIP_NOMEMORY;

    SCIP_CONS** tmp_ptr = cons_buff;
    for(size_t n = 0; n < nodes; n++) {
        SCIP_VAR** node_column = *set_color++;
        SCIP_VAR** tmp_enable_color = enable_color;
        for(size_t c = 0; c < colors; c++) {
            SCIP_CONS* curr = NULL;
            SCIP_CALL( SCIPcreateConsBasicKnapsack(scip, &curr, "", 0, NULL, NULL, 0));
            SCIP_CALL( SCIPaddCoefKnapsack(scip, curr, *node_column++, 1));
            SCIP_CALL( SCIPaddCoefKnapsack(scip, curr, *tmp_enable_color++, -1));
            *tmp_ptr++ = curr;
        }
    }

    *cons = cons_buff;
    return SCIP_OKAY;
}

SCIP_RETCODE build_model(Instance* instance) {
    // SCIP 
    SCIP_CALL (init_scip_env(&instance->scip_env));
    
    // Variables 
    SCIP_CALL ( add_bin_variable(instance->scip_env, &instance->color_enable, instance->color_count, 1.0));

    SCIP_CALL ( add_bin_matrix(instance->scip_env, &instance->color_selection, instance->node_count, instance->color_count, 0.0));

    // Constraints
    SCIP_CALL(add_one_color_per_node(instance->scip_env, &instance->one_color, instance->color_selection, instance->color_count, instance->node_count));
    SCIP_CALL(add_all_not_same_color(instance->scip_env, instance->color_selection, &instance->not_same_color, instance->graph->arcs, instance->graph->arcs_count, instance->color_count));
    SCIP_CALL(add_enable_color(instance->scip_env, instance->color_selection, instance->color_enable, &instance->enable_color, instance->node_count, instance->color_count));



    return SCIP_OKAY;
} 

