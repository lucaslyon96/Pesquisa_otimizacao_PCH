#include<iostream>
#include<fstream>
#define MAX 10
using namespace std;
int main(int argc, char **argv){
	char *filename = argv[1];
	ofstream save(filename);
	if(!save.is_open()){
		cout<<"Falha ao criar arquivo, verifique "<<endl;
		return 1;
	}
	double A[MAX][MAX]={};
	A[0][1]=281;
	A[0][2]=20.9;
	A[0][3]=18.1;
	A[0][4]=29;
	A[0][5]=39.7;
	A[0][6]=273;
	A[0][7]=214;
	A[0][8]=187;
	A[0][9]=38.4;
	A[1][2]=269;
	A[1][3]=263;
	A[1][4]=254;
	A[1][5]=255;
	A[1][6]=192;
	A[1][7]=73.7;
	A[1][8]=207;
	A[1][9]=286;
	A[2][3]=24.5;
	A[2][4]=16.5;
	A[2][5]=40.6;
	A[2][6]=261;
	A[2][7]=201;
	A[2][8]=175;
	A[2][9]=19.6;
	A[3][4]=9.3;
	A[3][5]=21.5;
	A[3][6]=255;
	A[3][7]=196;
	A[3][8]=169;
	A[3][9]=42.2;
	A[4][5]=30.8;
	A[4][6]=246;
	A[4][7]=187;
	A[4][8]=160;
	A[4][9]=33.4;
	A[5][6]=276;
	A[5][7]=188;
	A[5][8]=190;
	A[5][9]=63.4;
	A[6][7]=135;
	A[6][8]=87.3;
	A[6][9]=277;
	A[7][8]=140;
	A[7][9]=218;
	A[8][9]=192;
	for(int i=0;i<MAX;i++){
		for(int j=i+1;j<MAX;j++){
			A[i][i]=0;
			A[j][i]=A[i][j];
		}
	}
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			save<<A[i][j]<<" ";		
		}
		save<<endl;
	}
	return 0;
	save.close();

}


