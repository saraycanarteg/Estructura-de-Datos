#include <iostream>
#include "matrix_operations.cpp"
#include "Validation.cpp"

int main() {
    Validation<int> validation_int; 
    int size;

    do{
        cout<<"PROGRAMA DE MATRICES"<<endl;
        cout<<"Ingrese la dimension de la matriz cuadrada (max 20): ";
        
        size = validation_int.enter_a_number("int");

        if((size <= 1) || (size>20)){
            cout<<"\n\nDimension no valida. Intente de nuevo...\n";

            system("pause");
            system("cls");
        }

    }while((size <= 1) || (size>20));

    system("cls");
    cout<<"PROGRAMA DE MATRICES"<<endl;

    const size_t ROWS = size;
    const size_t COLS = size;

    try {
        // Crear dos matrices aleatorias
        auto matrix1 = MatrixOperations<int>::generateRandomMatrix(ROWS, COLS, 0, 20);
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