#include <iostream>
#include <vector>
#include <graphics.h>
#include <ctime>
#include "coloreo.h"

// Función para crear un grafo aleatorio
void crearGrafoAleatorio(int grafo[][MAX_VERTICES], int num_vertices) {
    // Inicializar grafo sin conexiones
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            grafo[i][j] = 0;
        }
    }

    // Generar conexiones aleatorias
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            // Probabilidad de conexión del 40%
            if (rand() % 100 < 40) {
                grafo[i][j] = grafo[j][i] = 1;
            }
        }
    }
}

int main() {
    // Configurar semilla aleatoria
    srand(time(NULL));

    int num_vertices, num_colores;

    // Instrucciones en consola
    std::cout << "PROBLEMA DE COLOREO DE GRAFOS" << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    // Solicitar número de vértices
    do {
        std::cout << "Ingrese el número de vértices (1-" << MAX_VERTICES << "): ";
        std::cin >> num_vertices;
    } while (num_vertices < 1 || num_vertices > MAX_VERTICES);

    // Crear grafo aleatorio
    int G[MAX_VERTICES][MAX_VERTICES];
    crearGrafoAleatorio(G, num_vertices);

    // Mostrar matriz de adyacencia
    std::cout << "\nMatriz de Adyacencia:" << std::endl;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            std::cout << G[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Solicitar número de colores
    do {
        std::cout << "\nIngrese el número de colores (m) a utilizar: ";
        std::cin >> num_colores;
    } while (num_colores < 1);

    // Inicializar gráficos
    initwindow(800, 600, "Coloreo de Grafo");

    // Vector para almacenar la solución de coloreo
    std::vector<int> colores(num_vertices, 0);

    // Llamar a la función de coloreo
    if (colorea(G, num_vertices, num_colores, colores)) {
        std::cout << "\nSolución de coloreo encontrada:" << std::endl;
        for (int i = 0; i < num_vertices; i++) {
            std::cout << "Vértice " << i << ": Color " << colores[i] << std::endl;
        }
        
        // Dibujar el grafo coloreado
        dibujarGrafo(G, num_vertices, colores);
    } else {
        std::cout << "No se encontró solución de coloreo con " 
                  << num_colores << " colores." << std::endl;
    }

    // Esperar entrada antes de cerrar
    getch();
    closegraph();

    return 0;
}