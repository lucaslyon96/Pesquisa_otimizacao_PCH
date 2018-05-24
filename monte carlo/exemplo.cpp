#include<iostream>
#include<fstream>
#include<cstdlib>
//#include<random>
//#include<chrono>

using namespace std;
#define MAX 100
struct Matriz{
	double dis[MAX][MAX];
};
Matriz func();
int main(){
	Matriz a;
	a.dis=func();
	cout<<a.dis<<endl;
}
Matriz func(){
	Matriz matriz;
	matriz.dis[0][0]=1;
	matriz.dis[0][1]=2;
	matriz.dis[1][0]=3;
	matriz.dis[1][1]=4;
	return matriz.dis;

}

