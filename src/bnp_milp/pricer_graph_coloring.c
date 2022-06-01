
#include <assert.h>

#include "bnp_milp.h"


#define PRICER_NAME            "graph-coloring"
#define PRICER_DESC            "Find coloring patterns"
#define PRICER_PRIORITY        0
#define PRICER_DELAY           TRUE     


struct SCIP_PricerData {
};


#define pricerCopyGraphColoring NULL

#define pricerFreeGraphColoring NULL

#define pricerInitGraphColoring NULL

#define pricerExitGraphColoring NULL

#define pricerInitsolGraphColoring NULL


#define pricerExitsolGraphColoring NULL

static
SCIP_DECL_PRICERREDCOST(pricerRedcostGraphColoring)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of GraphColoring variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}

#define pricerFarkasGraphColoring NULL



SCIP_RETCODE SCIPincludePricerGraphColoring(SCIP* scip) {
   SCIP_PRICERDATA* pricerdata;
   SCIP_PRICER* pricer;

   pricerdata = NULL;

   pricer = NULL;
   SCIP_CALL( SCIPincludePricerBasic(scip, &pricer, PRICER_NAME, PRICER_DESC, PRICER_PRIORITY, PRICER_DELAY,
         pricerRedcostGraphColoring, pricerFarkasGraphColoring, pricerdata) );
   assert(pricer != NULL);

   SCIP_CALL( SCIPsetPricerCopy(scip, pricer, pricerCopyGraphColoring) );
   SCIP_CALL( SCIPsetPricerFree(scip, pricer, pricerFreeGraphColoring) );
   SCIP_CALL( SCIPsetPricerInit(scip, pricer, pricerInitGraphColoring) );
   SCIP_CALL( SCIPsetPricerExit(scip, pricer, pricerExitGraphColoring) );
   SCIP_CALL( SCIPsetPricerInitsol(scip, pricer, pricerInitsolGraphColoring) );
   SCIP_CALL( SCIPsetPricerExitsol(scip, pricer, pricerExitsolGraphColoring) );

   return SCIP_OKAY;
}
