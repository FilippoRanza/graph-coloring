
#include <assert.h>

#include "bnp_milp.h"


#define PRICER_NAME            "graph-coloring"
#define PRICER_DESC            "Find coloring patterns"
#define PRICER_PRIORITY        0
#define PRICER_DELAY           TRUE


struct SCIP_PricerData {
   Graph* graph;
   SCIP_CONS** master_cons;
   int count;
};


SCIP_RETCODE initialize_pricing(SCIP** pricing) {

   SCIP_CALL( SCIPcreate(pricing) );
   SCIP_CALL( SCIPincludeDefaultPlugins(*pricing) );
   SCIP_CALL( SCIPcreateProbBasic(*pricing, "pricing") );
   SCIP_CALL( SCIPsetObjsense(*pricing, SCIP_OBJSENSE_MAXIMIZE) );
   SCIP_CALL( SCIPsetIntParam(*pricing, "display/verblevel", 0) );
   SCIP_CALL( SCIPsetBoolParam(*pricing, "misc/catchctrlc", FALSE) );
   SCIP_CALL( SCIPsetRealParam(*pricing, "limits/time", 25) );

   return SCIP_OKAY;
}

SCIP_RETCODE allocate_var_buffer(SCIP_VAR*** buff, SCIP* master, SCIP_PRICERDATA* pricer_data) {

   SCIP_VAR** vars;
   int count = pricer_data->count;
   SCIP_CALL(SCIPallocBufferArray(master, &vars, count));
   *buff = vars;
   return SCIP_OKAY;
}

SCIP_RETCODE create_variable(SCIP* master, SCIP* princing, SCIP_CONS* cons, SCIP_VAR** vars) {
   double dual = SCIPgetDualsolSetppc(master, cons);
   SCIP_VAR* var;
   SCIP_CALL(SCIPcreateVarBasic(princing, &var, "", 0.0, 1.0, dual, SCIP_VARTYPE_BINARY));
   SCIP_CALL( SCIPaddVar(princing, var) );
   *vars = var;
   SCIP_CALL(SCIPreleaseVar(princing, &var));
   return SCIP_OKAY;
}

SCIP_RETCODE create_pricer_vars(SCIP_VAR** vars, SCIP* master, SCIP* pricer, SCIP_CONS** conss, int count) {
   for(int i = 0; i < count; i++) {
      create_variable(master, pricer, *conss++, vars++);
   }
   return SCIP_OKAY;
}

SCIP_RETCODE create_pricing_constr(SCIP* pricing, Arc* arc, SCIP_VAR** vars) {
   SCIP_VAR* src = vars[arc->src];
   SCIP_VAR* dst = vars[arc->dst];
   SCIP_CONS* cons;
   
   SCIP_CALL(SCIPcreateConsBasicLinear(pricing, &cons, "", 0, NULL, NULL, 0.0, 1.0));
   SCIP_CALL(SCIPaddCoefLinear(pricing, cons, src, 1));
   SCIP_CALL(SCIPaddCoefLinear(pricing, cons, dst, 1));
   SCIP_CALL(SCIPaddCons(pricing, cons));
   SCIP_CALL(SCIPreleaseCons(pricing, &cons));

   return SCIP_OKAY;
}

SCIP_RETCODE create_pricing_constrs(SCIP* pricing, SCIP_PRICERDATA* pricer_data, SCIP_VAR** vars) {
   Graph* graph = pricer_data-> graph;
   Arc* arcs = graph->arcs;
   for(int i = 0; i < graph->arcs_count; i++, arcs++) {
      create_pricing_constr(pricing, arcs, vars);
   }

   return SCIP_OKAY;
}
SCIP_RETCODE create_pricing_problem(SCIP* master, SCIP_PRICER* pricer, SCIP* pricing, SCIP_VAR*** pricer_vars) {

   SCIP_PRICERDATA* pricer_data = SCIPpricerGetData(pricer);

   SCIP_VAR** var_buff;
   SCIP_CALL(allocate_var_buffer(&var_buff, master, pricer_data));
   SCIP_CALL(create_pricer_vars(var_buff, master, pricing, pricer_data->master_cons, pricer_data->count));
   SCIP_CALL(create_pricing_constrs(pricing, pricer_data, var_buff));

   *pricer_vars = var_buff;
   return SCIP_OKAY;
}

SCIP_RETCODE generate_column(SCIP* master, SCIP* pricing, SCIP_SOL* sol,  SCIP_VAR** vars, SCIP_CONS** conss, int count) {
         

   int* coeff;
   SCIP_CALL(SCIPallocBlockMemoryArray(master, &coeff, count));
   int* tmp = coeff;
   for(int i = 0; i < count; i++) {
      *tmp++ = SCIPgetSolVal(pricing, sol, *vars++);
   }

   SCIP_CALL(add_new_variable_direct(master, conss, coeff, count, 1));
  
   return SCIP_OKAY;
}

SCIP_RETCODE generate_columns(SCIP* master, SCIP* pricing, SCIP_PRICER* pricer, SCIP_VAR** vars, int* status) {
   SCIP_PRICERDATA* pricer_data = SCIPpricerGetData(pricer);
   int count = pricer_data->count;
   SCIP_CONS** conss = pricer_data->master_cons;

   SCIP_SOL** sols = SCIPgetSols(pricing);
   int sol_count = SCIPgetNSols(pricing);
   for(int i = 0; i < sol_count; i++) {
      SCIP_SOL* sol = *sols++;
      double sol_val = SCIPgetSolOrigObj(pricing, sol);
      if(SCIPisFeasGT(pricing, sol_val, 1.0)) {
         SCIP_CALL(generate_column(master, pricing, sol, vars, conss, count));
         *status = 1;
      } else {
         break;
      }
   }

   return SCIP_OKAY;
}
SCIP_RETCODE reduced_cost_pricing(SCIP* master, SCIP_PRICER* pricer, SCIP_Real* lowerbound, SCIP_Bool* stopearly, SCIP_RESULT* result) { 
   *result = SCIP_DIDNOTRUN;
   SCIP* pricing;
   SCIP_CALL( initialize_pricing(&pricing) );

   SCIP_VAR** pricer_vars;
   SCIP_CALL( create_pricing_problem(master, pricer, pricing, &pricer_vars) );

   SCIP_CALL( SCIPsolve(pricing) );

   int success = 0;
   SCIP_CALL( generate_columns(master, pricing, pricer, pricer_vars, &success) );


   if(success || SCIPgetStatus(pricing) == SCIP_STATUS_OPTIMAL) {
      *result = SCIP_SUCCESS;
   }

   SCIPfree(&pricing);
   SCIPfreeBufferArray(master, &pricer_vars);
   return SCIP_OKAY;
}


SCIP_RETCODE init_pricing_graph_coloring(SCIP* scip, SCIP_PRICER* pricer) {
   fprintf(stderr, "CALL Init\n");
   SCIP_PRICERDATA* pricer_data = SCIPpricerGetData(pricer);
   SCIP_CONS** conss = pricer_data->master_cons;
   int count = pricer_data->count;
   for(int i = 0; i < count; i++) {
      SCIP_CONS* tmp = *conss;

      SCIP_CALL( SCIPreleaseCons(scip, conss) );

      /* get transformed constraint */
      SCIP_CALL( SCIPgetTransformedCons(scip, tmp, conss) );

      /* capture transformed constraint */
      SCIP_CALL( SCIPcaptureCons(scip, *conss) );
      conss++;
   }



   return SCIP_OKAY;
}


SCIP_RETCODE init_pricer(BnPGraphColoring* bgc) {

   SCIP_PRICER* pricer;
   SCIP_CALL( SCIPincludePricerBasic(bgc->scip, &pricer, PRICER_NAME, PRICER_DESC, PRICER_PRIORITY, PRICER_DELAY,
         reduced_cost_pricing, NULL,NULL) );
   bgc->pricer = pricer;

   SCIP_CALL( SCIPsetPricerInit(bgc->scip, pricer, init_pricing_graph_coloring) );


   return SCIP_OKAY;
}

SCIP_RETCODE init_pricer_data(BnPGraphColoring* bgc) {
   SCIP_PRICERDATA* pricer_data;
   SCIP_CALL( SCIPallocBlockMemory(bgc->scip, &pricer_data));
   pricer_data->master_cons = bgc->master_cons;
   pricer_data->count = bgc->graph->node_count;
   pricer_data->graph = bgc->graph;

   SCIPpricerSetData(bgc->pricer, pricer_data);

   return SCIP_OKAY;
}


SCIP_RETCODE include_pricer_graph_coloring(BnPGraphColoring* bgc) {

   SCIP_CALL( init_pricer(bgc) );
   SCIP_CALL( init_pricer_data(bgc) );
   SCIP_CALL(SCIPactivatePricer(bgc->scip, bgc->pricer));

   return SCIP_OKAY;
}
