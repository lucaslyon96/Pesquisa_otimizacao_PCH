// -------------------------------------------------------------- -*- C++ -*-
// File: facility.cpp
// Version 12.6.1  
// --------------------------------------------------------------------------
// Licensed Materials - Property of IBM
// 5725-A06 5725-A29 5724-Y48 5724-Y49 5724-Y54 5724-Y55 5655-Y21
// Copyright IBM Corporation 2000, 2014. All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with
// IBM Corp.
// --------------------------------------------------------------------------
//

#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

typedef IloArray<IloNumArray>    FloatMatrix;
typedef IloArray<IloNumVarArray> NumVarMatrix;

int
main(int argc, char **argv)
{
 
 IloEnv env;
 IloModel model(env);
 IloCplex cplex(env);
 
 char *filename = argv[1];
 
 ifstream file(filename);
 
 if (!file) {
         cerr << "ERROR: could not open file '" << filename
              << "' for reading" << endl;
         cerr << "usage:   " << argv[0] << " <file>" << endl;
         throw(-1);
      }
 
 IloNum C, n;
 
 IloNumArray v(env), c(env), min(env);
 
 
 file >> C >> n;
 
 file >> v >> c >> min;

 IloNumVarArray x(env, n, 0, 10, ILOFLOAT);
 
 //cout << C << endl;
 //cout << n << endl;
 //cout << v << endl;
 //cout << c << endl;
 //cout << min << endl;
 
 
 	IloExpr obj(env);
 
 for(int i=0;i<n;i++)
 {
 	obj = obj + v[i]*x[i];
 }
 
 model.add(IloMaximize(env, obj));
 
// model.add(IloMaximize(env, IloScalProd(v, x));
 
 
 model.add(IloScalProd(c, x) <= C);
 
 for(int i=0;i<n;i++)
 {
 	model.add(x[i] >= min[i]);
 }
 
 cplex.extract(model);
 
 cplex.solve();
 
 cout << "Valor Nutricional = " << cplex.getObjValue() << endl;
 
 for(int i=0;i<n;i++)
 {
 	cout << "Alimento " << i << " " << cplex.getValue(x[i]) << endl;
 } 
 
 
   
   /* Problema da dieta não-genérico
   
   IloEnv env;
   //"ambiente": ligação com o software cplex
   IloModel modelo(env);
   // formulação do modelo a ser resolvido
   IloCplex cplex(env);
   //resolvedor -> solver
   
   IloNumVar x1(env, 0, 10, ILOFLOAT);
   IloNumVar x2(env, 0, 10, ILOFLOAT);
   IloNumVar x3(env, 0, 10, ILOFLOAT);
   IloNumVar x4(env, 0, 10, ILOFLOAT);
   IloNumVar x5(env, 0, 10, ILOFLOAT);
   
   IloExpr obj = 0.6*x1 + 0.5*x2 + 0.1*x3 + 0.2*x4 + 0.9*x5;
   
   modelo.add(IloMaximize(env, obj));
   
   IloExpr restricao1 = 300*x1 + 250*x2 + 1000*x3 + 100*x4 + 50*x5;
   
   modelo.add(restricao1 <= 2000);
   
   modelo.add(x3>=0.7);

	cplex.extract(modelo);
	
	cplex.solve();
	
	cout << "Valor Nutricional = " << cplex.getObjValue() << endl;
	
	float calorias = 300*cplex.getValue(x1) + 250*cplex.getValue(x2) + 1000*cplex.getValue(x3) + 100*cplex.getValue(x4) + 50*cplex.getValue(x5);
   
   cout << "Calorias = " << calorias << endl;
   
   cout << "Alimento 1 = " << cplex.getValue(x1) << endl; 
   cout << "Alimento 2 = " << cplex.getValue(x2) << endl; 
   cout << "Alimento 3 = " << cplex.getValue(x3) << endl; 
   cout << "Alimento 4 = " << cplex.getValue(x4) << endl; 
   cout << "Alimento 5 = " << cplex.getValue(x5) << endl; 
*/   
 
 /*  try {
      IloInt i, j;

      IloNumArray capacity(env), fixedCost(env);
      FloatMatrix cost(env);
      IloInt      nbLocations;
      IloInt      nbClients;

      const char* filename  = "../../../examples/data/facility.dat";
      if (argc > 1) 
         filename = argv[1];
      ifstream file(filename);
      if (!file) {
         cerr << "ERROR: could not open file '" << filename
              << "' for reading" << endl;
         cerr << "usage:   " << argv[0] << " <file>" << endl;
         throw(-1);
      }

      file >> capacity >> fixedCost >> cost;
      nbLocations = capacity.getSize();
      nbClients   = cost.getSize(); 

      IloBool consistentData = (fixedCost.getSize() == nbLocations);
      for(i = 0; consistentData && (i < nbClients); i++)
         consistentData = (cost[i].getSize() == nbLocations);
      if (!consistentData) {
         cerr << "ERROR: data file '" 
              << filename << "' contains inconsistent data" << endl;
         throw(-1);
      }

      IloNumVarArray open(env, nbLocations, 0, 1, ILOINT);
      NumVarMatrix supply(env, nbClients);
      for(i = 0; i < nbClients; i++)
         supply[i] = IloNumVarArray(env, nbLocations, 0, 1, ILOINT);

      IloModel model(env);
      for(i = 0; i < nbClients; i++)
         model.add(IloSum(supply[i]) == 1);
      for(j = 0; j < nbLocations; j++) {
         IloExpr v(env);
         for(i = 0; i < nbClients; i++)
            v += supply[i][j];
         model.add(v <= capacity[j] * open[j]);
         v.end();
      }

      IloExpr obj = IloScalProd(fixedCost, open);
      for(i = 0; i < nbClients; i++) {
         obj += IloScalProd(cost[i], supply[i]);
      }
      model.add(IloMinimize(env, obj));
      obj.end();

      IloCplex cplex(env);
      cplex.extract(model);
      cplex.solve();
	
      cplex.out() << "Solution status: " << cplex.getStatus() << endl;

      IloNum tolerance = cplex.getParam(
         IloCplex::Param::MIP::Tolerances::Integrality);
      cplex.out() << "Optimal value: " << cplex.getObjValue() << endl;
      for(j = 0; j < nbLocations; j++) {
         if (cplex.getValue(open[j]) >= 1 - tolerance) {
            cplex.out() << "Facility " << j << " is open, it serves clients ";
            for(i = 0; i < nbClients; i++) {
               if (cplex.getValue(supply[i][j]) >= 1 - tolerance)
                  cplex.out() << i << " ";
            }
            cplex.out() << endl; 
         }
      }
   }
   catch(IloException& e) {
      cerr  << " ERROR: " << e << endl;   
   }
   catch(...) {
      cerr  << " ERROR" << endl;   
   }*/
   env.end();
   return 0;
}
