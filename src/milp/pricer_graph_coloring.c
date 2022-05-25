
#include <assert.h>

#include "milp.h"


#define PRICER_NAME            "graph-coloring"
#define PRICER_DESC            "Find coloring patterns"
#define PRICER_PRIORITY        0
#define PRICER_DELAY           TRUE     





struct SCIP_PricerData
{
};

#if 0
static
SCIP_DECL_PRICERCOPY(pricerCopyXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}
#else
#define pricerCopyXyz NULL
#endif

/** destructor of variable pricer to free user data (called when SCIP is exiting) */
#if 0
static
SCIP_DECL_PRICERFREE(pricerFreeXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}
#else
#define pricerFreeXyz NULL
#endif


/** initialization method of variable pricer (called after problem was transformed) */
#if 0
static
SCIP_DECL_PRICERINIT(pricerInitXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}
#else
#define pricerInitXyz NULL
#endif


/** deinitialization method of variable pricer (called before transformed problem is freed) */
#if 0
static
SCIP_DECL_PRICEREXIT(pricerExitXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}
#else
#define pricerExitXyz NULL
#endif


/** solving process initialization method of variable pricer (called when branch and bound process is about to begin) */
#if 0
static
SCIP_DECL_PRICERINITSOL(pricerInitsolXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}
#else
#define pricerInitsolXyz NULL
#endif


/** solving process deinitialization method of variable pricer (called before branch and bound process data is freed) */
#if 0
static
SCIP_DECL_PRICEREXITSOL(pricerExitsolXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}
#else
#define pricerExitsolXyz NULL
#endif


/** reduced cost pricing method of variable pricer for feasible LPs */
static
SCIP_DECL_PRICERREDCOST(pricerRedcostXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}


#if 0
/** Farkas pricing method of variable pricer for infeasible LPs */
static
SCIP_DECL_PRICERFARKAS(pricerFarkasXyz)
{  /*lint --e{715}*/
   SCIPerrorMessage("method of xyz variable pricer not implemented yet\n");
   SCIPABORT(); /*lint --e{527}*/

   return SCIP_OKAY;
}
#else
#define pricerFarkasXyz NULL
#endif




/*
 * variable pricer specific interface methods
 */

/** creates the xyz variable pricer and includes it in SCIP */
SCIP_RETCODE SCIPincludePricerXyz(
   SCIP*                 scip                /**< SCIP data structure */
   )
{
   SCIP_PRICERDATA* pricerdata;
   SCIP_PRICER* pricer;

   /* create xyz variable pricer data */
   pricerdata = NULL;
   /* TODO: (optional) create variable pricer specific data here */

   pricer = NULL;

   /* include variable pricer */
#if 0
   /* use SCIPincludePricer() if you want to set all callbacks explicitly and realize (by getting compiler errors) when
    * new callbacks are added in future SCIP versions
    */
   SCIP_CALL( SCIPincludePricer(scip, PRICER_NAME, PRICER_DESC, PRICER_PRIORITY, PRICER_DELAY,
         pricerCopyXyz, pricerFreeXyz, pricerInitXyz, pricerExitXyz, 
         pricerInitsolXyz, pricerExitsolXyz, pricerRedcostXyz, pricerFarkasXyz,
         pricerdata) );
#else
   /* use SCIPincludePricerBasic() plus setter functions if you want to set callbacks one-by-one and your code should
    * compile independent of new callbacks being added in future SCIP versions
    */
   SCIP_CALL( SCIPincludePricerBasic(scip, &pricer, PRICER_NAME, PRICER_DESC, PRICER_PRIORITY, PRICER_DELAY,
         pricerRedcostXyz, pricerFarkasXyz, pricerdata) );
   assert(pricer != NULL);

   /* set non fundamental callbacks via setter functions */
   SCIP_CALL( SCIPsetPricerCopy(scip, pricer, pricerCopyXyz) );
   SCIP_CALL( SCIPsetPricerFree(scip, pricer, pricerFreeXyz) );
   SCIP_CALL( SCIPsetPricerInit(scip, pricer, pricerInitXyz) );
   SCIP_CALL( SCIPsetPricerExit(scip, pricer, pricerExitXyz) );
   SCIP_CALL( SCIPsetPricerInitsol(scip, pricer, pricerInitsolXyz) );
   SCIP_CALL( SCIPsetPricerExitsol(scip, pricer, pricerExitsolXyz) );
#endif


   return SCIP_OKAY;
}
