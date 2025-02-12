#include "dfs_animacion.h"
#include <graphics.h>
#include <cmath>
#include <iostream>
using namespace std;

DFSAnimacion::DFSAnimacion(Grafo* g) : grafoBase(g) {
    numVertices = g->getNumVertices();
    estados = new Estado[numVertices];
    for (int i = 0; i < numVertices; i++) {
        estados[i] = Estado::NO_VISITADO;
    }
    
    // Copiar coordenadas
    coordenadasX = new double[numVertices];
    coordenadasY = new double[numVertices];
    for(int i = 0; i < numVertices; i++) {
        coordenadasX[i] = g->getCoordX(i);
        coordenadasY[i] = g->getCoordY(i);
    }
    
    esDirigido = g->isDirigido();
    
    // Copiar matriz de adyacencia
    matrizAdy = new int*[numVertices];
    for(int i = 0; i < numVertices; i++) {
        matrizAdy[i] = new int[numVertices];
        for(int j = 0; j < numVertices; j++) {
            matrizAdy[i][j] = g->getConexion(i, j);
        }
    }
}

DFSAnimacion::~DFSAnimacion() {
    delete[] estados;
    delete[] coordenadasX;
    delete[] coordenadasY;
    
    for(int i = 0; i < numVertices; i++) {
        delete[] matrizAdy[i];
    }
    delete[] matrizAdy;
}

void DFSAnimacion::dibujarPila() {
    setfillstyle(SOLID_FILL, BLACK);
    bar(STACK_START_X - 50, 50, STACK_START_X + 100, getmaxy() - 50);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(STACK_START_X - 30, 50, "Pila DFS");
    
    std::stack<int> pilaTemp = pila;
    int y = STACK_START_Y;
    
    while (!pilaTemp.empty()) {
        rectangle(STACK_START_X - 20, y, 
                 STACK_START_X + 20, y + STACK_ELEMENT_HEIGHT);
        
        char num[3];
        sprintf(num, "%d", pilaTemp.top());
        outtextxy(STACK_START_X - 5, y + 10, num);
        
        pilaTemp.pop();
        y += STACK_ELEMENT_HEIGHT + 5;
    }
}

void DFSAnimacion::actualizarVertice(int v, Estado nuevoEstado) {
    estados[v] = nuevoEstado;
    
    int color;
    switch (nuevoEstado) {
        case Estado::NO_VISITADO: color = COLOR_NO_VISITADO; break;
        case Estado::EN_PROCESO: color = COLOR_EN_PROCESO; break;
        case Estado::VISITADO: color = COLOR_VISITADO; break;
    }
    
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(coordenadasX[v], coordenadasY[v], 20, 20);
    
    setcolor(BLACK);
    char label[3];
    sprintf(label, "%d", v);
    outtextxy(coordenadasX[v] - 5, coordenadasY[v] - 5, label);
    
    delay(DELAY_MS);
}

void DFSAnimacion::actualizarArista(int origen, int destino, bool esArbolDFS) {
    setcolor(esArbolDFS ? COLOR_ARISTA_ARBOL : COLOR_ARISTA_NORMAL);
    
    if (esDirigido) {
        double dx = coordenadasX[destino] - coordenadasX[origen];
        double dy = coordenadasY[destino] - coordenadasY[origen];
        double len = sqrt(dx*dx + dy*dy);
        double unitX = dx/len;
        double unitY = dy/len;
        
        int endX = coordenadasX[origen] + unitX * (len - 25);
        int endY = coordenadasY[origen] + unitY * (len - 25);
        
        line(coordenadasX[origen], coordenadasY[origen], endX, endY);
        
        double angle = atan2(dy, dx);
        int arrowSize = 10;
        line(endX, endY, 
             endX - arrowSize * cos(angle - M_PI/6),
             endY - arrowSize * sin(angle - M_PI/6));
        line(endX, endY,
             endX - arrowSize * cos(angle + M_PI/6),
             endY - arrowSize * sin(angle + M_PI/6));
    } else {
        if (origen < destino) {
            line(coordenadasX[origen], coordenadasY[origen],
                 coordenadasX[destino], coordenadasY[destino]);
        }
    }
}

void DFSAnimacion::dfsRecursivo(int v) {
    pila.push(v);
    actualizarVertice(v, Estado::EN_PROCESO);
    dibujarPila();
    
    for (int i = 0; i < numVertices; i++) {
        if (matrizAdy[v][i]) {
            if (estados[i] == Estado::NO_VISITADO) {
                actualizarArista(v, i, true);
                dfsRecursivo(i);
            } else {
                actualizarArista(v, i, false);
            }
        }
    }
    
    actualizarVertice(v, Estado::VISITADO);
    pila.pop();
    dibujarPila();
}

void DFSAnimacion::ejecutarDFS(int inicio) {
    if (inicio < 0 || inicio >= numVertices) {
        std::cout << "Vertice inicial invalido\n";
        return;
    }
    
    cleardevice();
    grafoBase->dibujarGrafo();
    
    dfsRecursivo(inicio);
}

