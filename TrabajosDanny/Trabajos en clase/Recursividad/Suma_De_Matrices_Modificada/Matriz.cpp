#include <iostream>
#include <time.h>
#include "Matriz.h"

using namespace std;

template<typename T>
Matriz<T>::Matriz(){}

template<typename T>
Matriz<T> :: Matriz(int rows, int columns, T number){
	this->rows = rows;
}

template<typename T>
T Matriz<T>::get_number(){
	return this->number;
}

template<typename T>
void Matriz<T>::set_number(T number){
	this->number = number;
}

template <typename T>
int Matriz<T>::get_rows(){
	return this-> rows;
}

template<typename T>
void Matriz<T>::set_rows(int rows){
	this->rows = rows;
}

template <typename T>
int Matriz<T>::get_columns(){
	return this-> columns;
}

template<typename T>
void Matriz<T>::set_columns(int columns){
	this->columns = columns;
}

template<typename T>
void Matriz<T>::generate_matrix(int **matrix, int rows, int columns){

	int i, j;

	srand(time(NULL));
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			matrix[i][j]=(int)((rand()/32768.1)*1000);
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}

}