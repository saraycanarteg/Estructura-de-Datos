#include <iostream>
#include <graphics.h>
#include <conio.h>
#include "solucion_grafica.h"

int main() {
    // Inicializar gráficos
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, "C:\\Turboc3\\BGI");

    // Comprobar si hay error en la inicialización de gráficos
    errorcode = graphresult();
    if (errorcode != grOk) {
        std::cout << "Error de inicialización de gráficos: " 
                  << grapherrormsg(errorcode) << std::endl;
        return 1;
    }

    // Número de vértices
    const int n = 5;

    // Matriz de adyacencia del grafo
    std::vector<std::vector<int>> grafo = {
        {0, 10, 15, 20, 25},
        {10, 0, 35, 25, 30},
        {15, 35, 0, 30, 20},
        {20, 25, 30, 0, 15},
        {25, 30, 20, 15, 0}
    };

    // Coordenadas de los vértices
    std::vector<std::vector<int>> coordenadas = {
        {300, 100},  // Vértice 0
        {450, 250},  // Vértice 1
        {350, 400},  // Vértice 2
        {250, 400},  // Vértice 3
        {150, 250}   // Vértice 4
    };

    // Instanciar solución gráfica
    SolucionGrafica sol(n, grafo, coordenadas);

    // Encontrar y mostrar ciclos hamiltonianos
    sol.encontrarCiclosHamiltonianos();

    // Esperar entrada
    getch();
    closegraph();

    return 0;
}