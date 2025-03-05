#include <iostream>
#include "solucion.h"

int main() {
    // Número de vértices
    const int n = 5;

    // Matriz de adyacencia del grafo
    int grafo[n][n] = {
        {0, 10, 15, 20, 25},
        {10, 0, 35, 25, 30},
        {15, 35, 0, 30, 20},
        {20, 25, 30, 0, 15},
        {25, 30, 20, 15, 0}
    };

    // Instanciar solución
    Solucion sol(n, (int*)grafo);

    // Encontrar ciclos hamiltonianos
    sol.encontrarCiclosHamiltonianos();

    return 0;
}