#include <iostream>
#include <vector>
#include <algorithm>

// Sintaxis con especificación del tipo de retorno

int main() {
    // Declarar una matriz (vector de vectores)
    std::vector<std::vector<int>> matriz = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Recorrer e imprimir la matriz usando lambdas con sintaxis diferente
    std::for_each(matriz.begin(), matriz.end(), [&](const std::vector<int>& fila) -> void {
        std::for_each(fila.begin(), fila.end(), [&](int num) -> void {
            std::cout << num << " ";
        });
        std::cout << std::endl;
    });

    return 0;
}
