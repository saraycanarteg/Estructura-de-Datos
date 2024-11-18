#pragma once
#include <iostream>

template <typename T>
class Matriz{
	private:

		int rows;
		int columns;
		T number;

	public:
		Matriz();
		Matriz(int, int, T);

		int get_rows();
		void set_rows(int);

		int get_columns();
		void set_columns(int);
		
		T get_number();
		void set_number(T);

		void generate_matrix(int *[], int , int);


};