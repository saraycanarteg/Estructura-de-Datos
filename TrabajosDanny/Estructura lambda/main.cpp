#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Lambda para sumar dos números
    auto suma = [](int x, int y) -> int {
        return x + y;
    };
    
    std::cout << "Suma: " << suma(3, 4) << std::endl; // Imprime 7

    // Lambda con captura por referencia
    int a = 10;
    auto capturaPorReferencia = [&a](int x) {
        a += x;
        return a;
    };
    std::cout << "Captura por referencia: " << capturaPorReferencia(5) << std::endl; // Imprime 15

    // Usando lambda con un algoritmo de la STL (sort)
    std::vector<int> vec = {5, 2, 8, 1, 3};
    std::sort(vec.begin(), vec.end(), [](int x, int y) { return x < y; });
    
    std::cout << "Vector ordenado: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
