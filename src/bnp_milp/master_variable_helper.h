
#ifndef __MASTER_VARIABLE_HELPER_H
#define __MASTER_VARIABLE_HELPER_H

#include "bnp_master.h"


SCIP_RETCODE add_new_variable(BnPGraphColoring*, int*, int);
SCIP_RETCODE add_new_variable_direct(SCIP*, SCIP_CONS**, int*, int, int);

#endif

