#ifndef SOLUCION_GRAFICA_H
#define SOLUCION_GRAFICA_H

#include <vector>

class SolucionGrafica {
private:
    int n;          // Número de vértices
    std::vector<std::vector<int>> grafo;     // Matriz de adyacencia como vector de vectores
    std::vector<std::vector<int>> coordenadas; // Coordenadas de los vértices como vector de vectores
    std::vector<int> camino;  // Camino actual
    std::vector<bool> visitado;  // Vértices visitados

    // Método privado de backtracking
    void backtracking(int k);

    // Método para dibujar el grafo
    void dibujarGrafo();

    // Método para dibujar un ciclo hamiltoniano
    void dibujarCiclo();

    // Método para verificar si es un ciclo válido
    bool esCicloValido();

public:
    // Constructor
    SolucionGrafica(int vertices, const std::vector<std::vector<int>>& matrizAdyacencia, 
                    const std::vector<std::vector<int>>& coordenadasVertices);

    // Método principal para encontrar ciclos hamiltonianos
    void encontrarCiclosHamiltonianos();
};

#endif // SOLUCION_GRAFICA_H