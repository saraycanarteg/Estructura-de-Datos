#include "solucion.h"
#include <iostream>

Solucion::Solucion(int vertices, int* matrizAdyacencia) : 
    n(vertices), 
    grafo(matrizAdyacencia), 
    camino(vertices), 
    visitado(vertices, false) {
}

void Solucion::encontrarCiclosHamiltonianos() {
    // Comenzamos siempre desde el vértice 0
    camino[0] = 0;
    visitado[0] = true;

    // Iniciamos el backtracking
    backtracking(1);
}

void Solucion::backtracking(int k) {
    // Si hemos completado un ciclo hamiltoniano
    if (k == n) {
        // Verificamos si es un ciclo válido
        if (esCicloValido()) {
            imprimirSolucion();
        }
        return;
    }

    // Probamos todos los posibles vértices para el siguiente paso
    for (int v = 0; v < n; v++) {
        // Condiciones para un vértice válido:
        // 1. No ha sido visitado
        // 2. Está conectado con el vértice anterior
        // 3. Si es el último paso, debe conectarse con el primer vértice
        if (!visitado[v] && 
            (k == 1 || grafo[camino[k-1] * n + v] != 0) &&
            (k < n-1 || grafo[camino[k-1] * n + v] != 0 && grafo[v * n + camino[0]] != 0)) {
            
            camino[k] = v;
            visitado[v] = true;

            // Recursión
            backtracking(k + 1);

            // Backtrack
            visitado[v] = false;
        }
    }
}

bool Solucion::esCicloValido() {
    // Verificamos que existan aristas entre todos los vértices del ciclo
    for (int i = 0; i < n-1; i++) {
        if (grafo[camino[i] * n + camino[i+1]] == 0) {
            return false;
        }
    }

    // Verificamos la conexión del último al primer vértice
    return grafo[camino[n-1] * n + camino[0]] != 0;
}

void Solucion::imprimirSolucion() {
    std::cout << "Ciclo Hamiltoniano encontrado: ";
    for (int i = 0; i < n; i++) {
        std::cout << camino[i] << " ";
    }
    std::cout << camino[0] << std::endl;  // Volvemos al inicio
}