#ifndef SOLUCION_H
#define SOLUCION_H

#include <vector>

class Solucion {
private:
    int n;          // Número de vértices
    int* grafo;     // Matriz de adyacencia
    std::vector<int> camino;  // Camino actual
    std::vector<bool> visitado;  // Vértices visitados

    // Método privado de backtracking
    void backtracking(int k);

    // Método para imprimir solución
    void imprimirSolucion();

    // Método para verificar si es un ciclo válido
    bool esCicloValido();

public:
    // Constructor
    Solucion(int vertices, int* matrizAdyacencia);

    // Método principal para encontrar ciclos hamiltonianos
    void encontrarCiclosHamiltonianos();
};

#endif // SOLUCION_H