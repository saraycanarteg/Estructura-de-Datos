#ifndef DLRMATRIX_H
#define DLRMATRIX_H

#include <iostream>
#include <vector>
#include <any>
#include <stdexcept>

using namespace std;

class DLRMatrix {
private:
    int rows, cols;                       // Dimensiones de la matriz
    vector<vector<any>> data;              // Almacenamiento de datos con tipo `any`

public:
    DLRMatrix(int rows, int cols);         // Constructor para inicializar la matriz
    void set(int row, int col, any value); // Setter general para cualquier tipo de dato
    template <typename T>
    T get(int row, int col) const;         // Getter general para cualquier tipo de dato
    void print() const;                    // Imprime la matriz
};

#endif
