#include<iostream>
#include<fstream>
#include<cstdlib>
#include <tr1/random>
using namespace std;
using namespace std::tr1;
#define MAX 100
void salve(int n, double dis[][MAX], ofstream & escrita);
double matrizd2(int,int[][MAX],int,double dis[][MAX]);
double matrizd1(int,int[][MAX],int,double dis[][MAX]);
int main(int argc, char **argv){   
	if(argc<7){
		cout<<" <nome arq entrada>  <nome arq saida> <media(a)> <desvio padrao(b) <dissimilaridade(1 ou 2)> <seed> "<<endl;
		return -1;
	}
	char *filename=argv[1];
	char *savename=argv[2];
	double a=atof(argv[3]);
	double b=atof(argv[4]);
	int d=atoi(argv[5]);
	int seed=atoi(argv[6]);
	variate_generator<mt19937, normal_distribution<> > r(mt19937(time(NULL)), normal_distribution<>(a, b));
	ofstream escrita(savename);
	if(!escrita.is_open()){
		cout<<"falha ao abrir o arquivo! verifique o nome dado"<<endl;
		return 1;
	}
	ifstream file(filename);
	if(!file.is_open()){
		cout<<"falha ao abrir o arquivo! verifique o nome dado"<<endl;
		return 1;
	}
	int p,n,seeda,A[MAX][MAX];
	file>>p>>n>>seeda;
	escrita<<p<<" "<<n<<endl;
	for(int i=0;i<p;i++){
		for(int j=0;j<n;j++){
			file>>A[i][j];
		}
	}
	double number;
	double dis[MAX][MAX];
	if(d==1){
		matrizd1(n,A,p,dis);
	}
	else if(d==2) {
		matrizd2(n,A,p,dis);
	}
	else {
		cout<<"Tipo de dissimilaridade invalida!"<<endl;
		return -1;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){			
			if(i!=j){
				number= r();
				dis[i][j]=dis[i][j]+number;
				if(dis[i][j]<0){
					dis[i][j]=0;
				}
				else if (dis[i][j]>1){
					dis[i][j]=1;
				}
			}
			
		}
	}
	salve(n,dis,escrita);
	cout<<"Finish"<<endl;
	escrita.close();
	return 0;
}
double matrizd1(int n,int A[][MAX],int p,double dis[][MAX]){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			dis[i][j]=1;
		}
	}
	float soma=0;	
	int vetor[n];
	for (int ia=0;ia<p;ia++){
		for(int i=0;i<n;i++){
		vetor[i]=-1;
	}
		soma=0;
		for(int ja=0;ja<n;ja++){
			soma+=A[ia][ja];
		}
		int cont=0;
		for(int ja=0;ja<n;ja++){
			if(A[ia][ja]==1){
				vetor[cont]=ja;
				cont++;
			}	
		}
		for(int i=0;i<n;i++){			
			for(int j=0;j<n;j++){
				if(vetor[i]!=-1 && vetor[i+j]!=-1 && (i+j)<n){
					dis[vetor[i]][vetor[i+j]]=1-(1.0/soma);
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j!=i){
				dis[j][i]=dis[i][j];
			}
			dis[i][i]=0;
		}
	}
	return 1;
}
double matrizd2(int n,int A[][MAX],int p,double dis[][MAX]){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			dis[i][j]=1;
		}
	}
	float soma=0;	
	int vetor[n];
	for (int ia=0;ia<p;ia++){
		for(int i=0;i<n;i++){
		vetor[i]=-1;
	}
		soma=0;
		for(int ja=0;ja<n;ja++){
			soma+=A[ia][ja];
		}
		int cont=0;
		for(int ja=0;ja<n;ja++){
			if(A[ia][ja]==1){
				vetor[cont]=ja;
				cont++;
			}	
		}
		for(int i=0;i<n;i++){			
			for(int j=0;j<n;j++){
				if(vetor[i]!=-1 && vetor[i+j]!=-1 && (i+j)<n){
					dis[vetor[i]][vetor[i+j]]=0;
				}
			}	
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j!=i){
				dis[j][i]=dis[i][j];
			}
			dis[i][i]=0;
		}
	}
	return 1;
}
void salve(int n, double dis[][MAX], ofstream & escrita){
	for(int i=0;i<n;i++){
		if(i==0){
		escrita<<"[";
		}
		escrita<<"[";
		for(int j=0;j<n;j++){
			escrita<<dis[i][j];
			if(j!=n-1){
			escrita<<",";
			}
		}
		escrita<<"]";
		if(i<n-1){
			escrita<<",";
		}
		if(i==n-1){
			escrita<<"]";
		}
		escrita<<endl;
	}	
}
