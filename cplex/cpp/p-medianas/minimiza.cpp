#include <ilcplex/ilocplex.h>
#include<iostream>
#include <fstream>
#include<iomanip>
using namespace std;
ILOSTLBEGIN
int main(int argc, char **argv)
{
 
 IloEnv env;
 IloModel model(env);
 IloCplex cplex(env);
 
 char *filename = argv[1];
 char *filenamesaida = argv[2];
 //outro arquivo para analise
 //mostrar os paraemetro que sera utilizado no terminal 
 ifstream file(filename);
 ofstream salve(filenamesaida);
	if( !salve.is_open() ){
		cout <<"Falha ao abrir o arquivo!" <<endl;
		return 1;
	}
	if (!file) {
		cerr << "ERROR: could not open file '" << filename
		   	 << "' for reading" << endl;
		cerr << "usage:   " << argv[0] << " <file>" << endl;
		throw(-1);
	}
 	IloNum p,n; //criacao de variaveis 
 	file>>p>>n; //gravando do arquivos as variaveis
 	IloArray<IloNumArray> D(env); // criando um array de array (matriz)
 	file>>D;//gravando em D a matriz do arquivo 
 	IloArray<IloNumVarArray> x(env, n);
 	for(int i=0;i<n;i++){
 		x[i]=IloNumVarArray(env,n);
 	}
 	for(int i=0;i<n;i++){
 		for(int j=0;j<n;j++){
 			if(i==j){
 				x[i][j]=IloNumVar(env,0,1,ILOBOOL);
 			}
 			else {
 				x[i][j]=IloNumVar(env,0,1,ILOFLOAT);
 			}
 		}
 	}
 	cplex.setParam(IloCplex::Threads,1);
 	double tempo;
 	tempo=60;
 	cplex.setParam(IloCplex::TiLim,60*60);
  	IloExpr obj(env);
 	for(int i=0;i<n;i++){ 
 		for(int j=0;j<n;j++){
 			obj+=D[i][j]*x[i][j];//definicao do objetivo 
 		}
 	}
 	for(int i=0;i<n;i++){
 		IloExpr	rest1(env);//
 		for(int j=0;j<n;j++){
 			rest1+=x[i][j];
 		}
		model.add(rest1==1);//cada lina pode ter apenas um objeto 
 	}
 	IloExpr rest2(env);//a quantidade de medianas tem q ser igual a quandidade fornecida em p
 	for(int i=0;i<n;i++){
 		rest2+=x[i][i];
 	}
 	model.add(rest2==p);
 	for(int i=0;i<n;i++){
 		for(int j=0;j<n;j++){
 			model.add(x[i][j]<=x[j][j]);//os elementos precisam ser menor do que os elementos na diagonal principal
 		}
 	}
 	model.add(IloMinimize(env,obj));//chamando o modelo"metodo simples"
 	cplex.extract(model);//extraindo o modelo "metodo simples"
 	cplex.solve();//resolvendo o modelo "metodo simples"
 	double LB,UB,GAP;//LB = Lower bound; UB=Upper Bound;Gap = porcentagem da relacao LB POR UB 
 	LB=cplex.getBestObjValue();
 	UB=cplex.getObjValue();
 	GAP=(1-(LB/UB))*100;
 	//http://www.ibm.com/support/knowledgecenter/SSSA5P_12.6.1/ilog.odms.cplex.help/refcppcplex/html/classes/IloCplex_MIPInfoCallbackI.html%23method_getNnodes?lang=pt-br
 	salve<<"nós de branch and bound = "<<cplex.getNnodes()<<endl;//pega o numero de nos de branch and bound (duvida: porque para usar este comando nao precisei entrar na classe ?
 	salve<<"GAP = "<<GAP<<"%"<<endl;
 	salve<<"LB = "<<LB<<endl;
 	salve<<"UB = "<<UB<<endl;
 	salve<<"melhor custo = "<<cplex.getObjValue()<<endl;
 	for(int i=0;i<n;i++){
 		for(int j=0;j<n;j++){
 			salve<<setw(10)<<cplex.getValue(x[i][j]);
 		}
 		salve<<endl;
 	}
 	salve.close();
 	cout<<"melhor custo = "<<cplex.getObjValue()<<endl;
	
	return 0;	 	
}
 	
 	
