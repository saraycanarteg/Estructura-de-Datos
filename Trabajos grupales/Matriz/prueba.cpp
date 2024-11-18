#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Declarar una matriz (vector de vectores)
    std::vector<std::vector<int>> matriz = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Recorrer e imprimir la matriz usando for_each y lambdas
    std::for_each(matriz.begin(), matriz.end(), [](const std::vector<int>& fila) {
        std::for_each(fila.begin(), fila.end(), [](int num) {
            std::cout << num << " ";
        });
        std::cout << std::endl;
    });

    return 0;
}
