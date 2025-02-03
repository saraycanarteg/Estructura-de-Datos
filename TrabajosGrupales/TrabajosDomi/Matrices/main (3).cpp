#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 3
/*
Suma de matrices recursiva
*/

using namespace std;

void sumaRecursivaMatrices(int[MAX][MAX], int[MAX][MAX], int[MAX][MAX], int, int);

void sumaRecursivaMatrices(int mat1[MAX][MAX], int mat2[MAX][MAX], int matr[MAX][MAX], int f, int c) {
    // Caso base
    if (f == 0 && c == 0) {
        matr[f][c] = mat1[f][c] + mat2[f][c];
    } else {
        // Asigna el resultado a la posición actual
        matr[f][c] = mat1[f][c] + mat2[f][c];
        
        // Lógica para recorrer la matriz
        if (c > 0) {
            sumaRecursivaMatrices(mat1, mat2, matr, f, c - 1);
        } else if (f > 0) {
            sumaRecursivaMatrices(mat1, mat2, matr, f - 1, MAX - 1);
        }
    }
}

int main(int argc, char** argv) {
    int mat1[MAX][MAX], mat2[MAX][MAX], matr[MAX][MAX];
    srand(time(NULL));
    
    // Genera matrices aleatorias mat1 y mat2
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            mat1[i][j] = (int)((rand() / 32768.1) * 1000);
            mat2[i][j] = (int)((rand() / 32768.1) * 1000);
        }
    }
    
    // Muestra la matriz mat1
    cout << "Matriz 1:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat1[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Muestra la matriz mat2
    cout << "Matriz 2:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat2[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Llama a la función recursiva para sumar las matrices y almacenar el resultado en matr
    sumaRecursivaMatrices(mat1, mat2, matr, MAX - 1, MAX - 1);
    
    // Muestra la matriz resultante de la suma (matr)
    cout << "Suma de Matrices:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << matr[i][j] << "\t";
        }
        cout << endl;
    }
    
    return 0;
}