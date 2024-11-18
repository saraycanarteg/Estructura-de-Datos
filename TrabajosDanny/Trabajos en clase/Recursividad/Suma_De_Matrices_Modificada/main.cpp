#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Matriz.cpp"
#define MAX 3
/*
Suma de matrices recursiva
*/

using namespace std;

int sumaRecursivaMatrices(int[MAX][MAX], int[MAX][MAX], int, int);

void printMatrix(int *[]);
//int sumaRecursivaMatrices(int**, int**, int, int);

int sumaRecursivaMatrices(int mat1[MAX][MAX], int mat2[MAX][MAX], int f, int c){
	if((f==0)&&(c==0))
		return mat1[f][c]+mat2[f][c];
	else{
		if(f>-1){
			c--;
			if(c>=-1)
				return mat1[f][c+1]+mat2[f][c+1]+sumaRecursivaMatrices(mat1, mat2, f, c);
			else
				return sumaRecursivaMatrices(mat1, mat2, f-1, 2);
		}
	}
	//return;
}

int main() {
	int mat1[MAX][MAX], mat2[MAX][MAX];
	
	int matrix[3][3];

	Matriz<int> matrixx;
	matrixx.generate_matrix(matrix[3], 3,3);
	

	
	/*for(int i=0; i<MAX; i++){
		for(int j=0; j<MAX; j++){
			cout<<mat1[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	
	for(int i=0; i<MAX; i++){
		for(int j=0; j<MAX; j++){
			cout<<mat2[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<"Suma de Matrices es: "<< sumaRecursivaMatrices(mat1, mat2, 2, 2);*/
	return 0;
}

void printMatrix(int mat, int dimension){

	int i;
	for(i=0;i<3;i++){
	}
		

}