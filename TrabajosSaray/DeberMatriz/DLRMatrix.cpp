#include "DLRMatrix.h"

// Constructor de DLRMatrix que inicializa la matriz con dimensiones específicas
DLRMatrix::DLRMatrix(int rows, int cols) : rows(rows), cols(cols), data(rows, vector<any>(cols)) {}

// Setter que asigna cualquier tipo de valor a una posición específica
void DLRMatrix::set(int row, int col, any value) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        data[row][col] = value;
    } else {
        throw out_of_range("Índice fuera de rango");
    }
}

// Getter genérico para obtener el valor en una posición específica, de tipo `T`
template <typename T>
T DLRMatrix::get(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return any_cast<T>(data[row][col]);
    } else {
        throw out_of_range("Índice fuera de rango");
    }
}

// Método para imprimir la matriz de cualquier tipo
void DLRMatrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            try {
                if (data[i][j].type() == typeid(int))
                    cout << any_cast<int>(data[i][j]) << " ";
                else if (data[i][j].type() == typeid(float))
                    cout << any_cast<float>(data[i][j]) << " ";
                else if (data[i][j].type() == typeid(double))
                    cout << any_cast<double>(data[i][j]) << " ";
                else
                    cout << "Tipo desconocido ";
            } catch (const bad_any_cast& e) {
                cout << "Error: " << e.what();
            }
        }
        cout << endl;
    }
}
