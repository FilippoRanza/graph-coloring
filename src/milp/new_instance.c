#include "milp.h"


Instance* init_instance(Graph* g, size_t c) {
    Instance* instance = malloc(sizeof(Instance));
    if(instance == NULL) 
        return NULL;
    instance->graph = g;
    instance->color_count = c;
    instance->node_count = g->node_count;

    instance->scip_env = NULL;
    instance->color_enable = NULL;
    instance->color_selection = NULL;
    instance->one_color = NULL;
    instance->not_same_color = NULL;
    instance->enable_color = NULL;

    return instance;
}


Instance* new_instance(Graph* graph, size_t color_count) {
    Instance* instance = init_instance(graph, color_count);
    if(instance == NULL)
        return NULL;

    SCIP_RETCODE code = build_model(instance);
    if(code != SCIP_OKAY) {
        free_instance(instance);
        return NULL;
    }

    return instance;
}
