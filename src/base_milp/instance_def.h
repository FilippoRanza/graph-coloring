

typedef struct {
    SCIP* scip_env;
    SCIP_VAR** color_enable;
    SCIP_VAR*** color_selection;
    SCIP_CONS** one_color;
    SCIP_CONS** not_same_color;
    SCIP_CONS** enable_color;
    Graph* graph;
    size_t color_count;
    size_t node_count;
} Instance;


