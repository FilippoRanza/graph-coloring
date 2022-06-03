#ifndef __BNP_MASTER_H
#define __BNP_MASTER_H

#include <scip/scip.h>
#include "bnp_milp.h"

SCIP_RETCODE create_bnp_master(BnPGraphColoring*);
SCIP_RETCODE enable_pricing(BnPGraphColoring*);


#endif
