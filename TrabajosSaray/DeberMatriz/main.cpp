#include <iostream>
#include "DLRMatrix.h"

int main() {
    int rows = 3, cols = 3;
    
    // Crear una instancia de DLRMatrix para una matriz 3x3
    DLRMatrix matrix(rows, cols);

    // Asignar diferentes tipos de valores a la matriz
    matrix.set(0, 0, 10);          // Entero
    matrix.set(0, 1, 20.5f);       // Float
    matrix.set(0, 2, 30.7);        // Double

    matrix.set(1, 0, 40);          // Entero
    matrix.set(1, 1, 50.9f);       // Float
    matrix.set(1, 2, 60.3);        // Double

    matrix.set(2, 0, 70);          // Entero
    matrix.set(2, 1, 80.1f);       // Float6
    matrix.set(2, 2, 90.2);        // Double

    // Imprimir la matriz con diferentes tipos
    cout << "Contenido de la matriz:" << endl;
    matrix.print();

    // Obtener valores específicos con tipo
    try {
        int val = matrix.get<int>(0, 0);
        cout << "\nValor en (0, 0) como int: " << val << endl;
    } catch (const bad_any_cast& e) {
        cout << "Error en la conversión de tipo: " << e.what() << endl;
    }

    return 0;
}
