
#ifndef __BNP_COLORING_STRUCT
#define __BNP_COLORING_STRUCT

struct SCIP_VarData {
    int* coeff;
    int count;
};

typedef struct {
    Graph* graph;
    SCIP* scip;
    SCIP_CONS** master_cons;
} BnPGraphColoring;

SCIP_RETCODE init_instance(BnPGraphColoring**, Graph*);
SCIP_RETCODE free_instance(BnPGraphColoring*);

#endif