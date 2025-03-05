#include "solucion_grafica.h"
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <dos.h>

SolucionGrafica::SolucionGrafica(int vertices, 
                                 const std::vector<std::vector<int>>& matrizAdyacencia, 
                                 const std::vector<std::vector<int>>& coordenadasVertices) : 
    n(vertices), 
    grafo(matrizAdyacencia), 
    coordenadas(coordenadasVertices),
    camino(vertices), 
    visitado(vertices, false) {
}

void SolucionGrafica::encontrarCiclosHamiltonianos() {
    // Dibujar grafo base
    dibujarGrafo();

    // Comenzamos siempre desde el vértice 0
    camino[0] = 0;
    visitado[0] = true;

    // Iniciamos el backtracking
    backtracking(1);
}

void SolucionGrafica::backtracking(int k) {
    // Si hemos completado un ciclo hamiltoniano
    if (k == n) {
        // Verificamos si es un ciclo válido
        if (esCicloValido()) {
            dibujarCiclo();
            delay(2000);  // Mostrar cada solución 2 segundos
            dibujarGrafo();  // Restaurar grafo base
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
            (k == 1 || grafo[camino[k-1]][v] != 0) &&
            (k < n-1 || grafo[camino[k-1]][v] != 0 && grafo[v][camino[0]] != 0)) {
            
            camino[k] = v;
            visitado[v] = true;

            // Recursión
            backtracking(k + 1);

            // Backtrack
            visitado[v] = false;
        }
    }
}

bool SolucionGrafica::esCicloValido() {
    // Verificamos que existan aristas entre todos los vértices del ciclo
    for (int i = 0; i < n-1; i++) {
        if (grafo[camino[i]][camino[i+1]] == 0) {
            return false;
        }
    }

    // Verificamos la conexión del último al primer vértice
    return grafo[camino[n-1]][camino[0]] != 0;
}

void SolucionGrafica::dibujarGrafo() {
    // Limpiar pantalla
    cleardevice();

    // Dibujar aristas
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (grafo[i][j] != 0) {
                // Conectar vértices con líneas
                line(coordenadas[i][0], coordenadas[i][1], 
                     coordenadas[j][0], coordenadas[j][1]);
            }
        }
    }

    // Dibujar vértices
    for (int i = 0; i < n; i++) {
        char vertice[3];
        sprintf(vertice, "%d", i);
        
        // Círculo para cada vértice
        circle(coordenadas[i][0], coordenadas[i][1], 20);
        
        // Etiqueta del vértice
        outtextxy(coordenadas[i][0]-5, coordenadas[i][1]-10, vertice);
    }
}

void SolucionGrafica::dibujarCiclo() {
    // Limpiar pantalla
    cleardevice();

    // Dibujar vértices
    for (int i = 0; i < n; i++) {
        char vertice[3];
        sprintf(vertice, "%d", camino[i]);
        
        // Círculo para cada vértice
        circle(coordenadas[camino[i]][0], coordenadas[camino[i]][1], 20);
        
        // Etiqueta del vértice
        outtextxy(coordenadas[camino[i]][0]-5, coordenadas[camino[i]][1]-10, vertice);
    }

    // Dibujar ciclo hamiltoniano
    for (int i = 0; i < n-1; i++) {
        line(coordenadas[camino[i]][0], coordenadas[camino[i]][1], 
             coordenadas[camino[i+1]][0], coordenadas[camino[i+1]][1]);
    }

    // Cerrar el ciclo
    line(coordenadas[camino[n-1]][0], coordenadas[camino[n-1]][1], 
         coordenadas[camino[0]][0], coordenadas[camino[0]][1]);
}