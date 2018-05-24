#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
#define MAX 100
int main(int argc, char **argv){
	if(argc<5){
		cout<<" <nome arq saida> <cluster(p)> <objetos(n) <seed> "<<endl;
		return -1;
	}
	char *savename=argv[1];
	int p=atoi(argv[2]);
	int n=atoi(argv[3]);
	int seed=atoi(argv[4]);
	
	
	srand(seed);
	ofstream save(savename);
	if(!save.is_open()){
		cout<<"falha ao abrir o arquivo! verifique o nome dado"<<endl;
		return 1;
	}
	int matriz[MAX][MAX];
	int sort;
	save<<p<<" "<<n<<" "<<seed<<endl;
	for(int i=0;i<n;i++){
		sort=rand()%3;
		matriz[sort][i]=1; 
		for(int j=0;j<p;j++){
			if(sort!=j){
				matriz[j][i]=0;
			}
		}
	}
	for(int i=0;i<p;i++){
		for(int j=0;j<n;j++){
			save<<matriz[i][j]<<" ";
		}
		save<<endl;
	}
	cout<<"finish"<<endl;
	return 0;
}
