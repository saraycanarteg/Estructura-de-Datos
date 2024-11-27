#include "matrix_operations.cpp"
#include <iostream>

int main() {
    const size_t ROWS = 3;
    const size_t COLS = 3;

    try {
        // Crear dos matrices aleatorias
        auto matrix1 = MatrixOperations<int>::generateRandomMatrix(ROWS, COLS, 0, 10);
        auto matrix2 = MatrixOperations<int>::generateRandomMatrix(ROWS, COLS, 10, 20);

        std::cout << "Matriz 1:" << std::endl;
        matrix1.print();

        std::cout << "Matriz 2:" << std::endl;
        matrix2.print();

        std::cout << "Resultado de la suma recursiva:" << std::endl;
        auto result = matrix1.recursiveSum(matrix2);
        result.print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}