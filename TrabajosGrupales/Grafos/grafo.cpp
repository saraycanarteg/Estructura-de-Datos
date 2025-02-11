#include "grafo.h"
#include <graphics.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Implementación de ListaEnlazada
ListaEnlazada::~ListaEnlazada() {
    limpiar();
}

void ListaEnlazada::insertar(int dato) {
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void ListaEnlazada::limpiar() {
    while(cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Implementación de Grafo
Grafo::Grafo(int vertices, bool esDirigido) : numVertices(vertices), dirigido(esDirigido) {
    // Inicializar matriz de adyacencia
    matrizAdyacencia = new int*[numVertices];
    for(int i = 0; i < numVertices; i++) {
        matrizAdyacencia[i] = new int[numVertices];
    }
    inicializarMatriz();
    
    // Inicializar lista de adyacencia
    listaAdyacencia = new ListaEnlazada[numVertices];
    
    // Inicializar coordenadas
    coordX = new double[numVertices];
    coordY = new double[numVertices];
}

Grafo::~Grafo() {
    liberarMatriz();
    delete[] listaAdyacencia;
    delete[] coordX;
    delete[] coordY;
}

void Grafo::inicializarMatriz() {
    for(int i = 0; i < numVertices; i++) {
        for(int j = 0; j < numVertices; j++) {
            matrizAdyacencia[i][j] = 0;
        }
    }
}

void Grafo::liberarMatriz() {
    for(int i = 0; i < numVertices; i++) {
        delete[] matrizAdyacencia[i];
    }
    delete[] matrizAdyacencia;
}

void Grafo::limpiarGrafo() {
    inicializarMatriz();
    for(int i = 0; i < numVertices; i++) {
        listaAdyacencia[i].limpiar();
    }
}

void Grafo::generarGrafoAleatorio() {
    limpiarGrafo();
    srand(time(nullptr));
    
    // Generar coordenadas en círculo
    double angulo = 2 * M_PI / numVertices;
    int radio = 150;
    int centroX = getmaxx() / 2;
    int centroY = getmaxy() / 2;
    
    for(int i = 0; i < numVertices; i++) {
        coordX[i] = centroX + radio * cos(i * angulo);
        coordY[i] = centroY + radio * sin(i * angulo);
    }
    
    // Generar conexiones aleatorias
    for(int i = 0; i < numVertices; i++) {
        for(int j = 0; j < numVertices; j++) {
            if(i != j && rand() % 2) {
                matrizAdyacencia[i][j] = 1;
                listaAdyacencia[i].insertar(j);
                
                if(!dirigido && i < j) {
                    matrizAdyacencia[j][i] = 1;
                    listaAdyacencia[j].insertar(i);
                }
            }
        }
    }
}

void Grafo::dibujarMatrizGrafica() const {
    cleardevice();
    setbkcolor(BLACK);
    cleardevice();
    
    int cellSize = 40;
    int startX = getmaxx() / 2 - (numVertices * cellSize) / 2;
    int startY = 50;
    
    // Dibujar título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 100, 10, "Matriz de Adyacencia");
    
    // Dibujar números de columnas
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    for(int j = 0; j < numVertices; j++) {
        char num[3];
        sprintf(num, "%d", j);
        outtextxy(startX + j * cellSize + cellSize/2 - 5, startY - 20, num);
    }
    
    // Dibujar números de filas y matriz
    for(int i = 0; i < numVertices; i++) {
        char num[3];
        sprintf(num, "%d", i);
        outtextxy(startX - 20, startY + i * cellSize + cellSize/2 - 5, num);
        
        for(int j = 0; j < numVertices; j++) {
            rectangle(startX + j * cellSize, startY + i * cellSize,
                     startX + (j+1) * cellSize, startY + (i+1) * cellSize);
            
            char val[2];
            sprintf(val, "%d", matrizAdyacencia[i][j]);
            outtextxy(startX + j * cellSize + cellSize/2 - 5,
                     startY + i * cellSize + cellSize/2 - 5, val);
        }
    }
}

void Grafo::dibujarListaGrafica() const {
    cleardevice();
    setbkcolor(BLACK);
    cleardevice();
    
    int startX = 80;
    int startY = 80;
    int vertSpace = 50;
    int horizSpace = 50;
    
    // Dibujar título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 100, 20, "Lista de Adyacencia");
    
    // Dibujar lista
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    for(int i = 0; i < numVertices; i++) {
        // Dibujar vértice
        char vertex[3];
        sprintf(vertex, "%d", i);
        outtextxy(startX, startY + i * vertSpace, vertex);
        outtextxy(startX + 20, startY + i * vertSpace, "->");
        
        // Dibujar lista de adyacencia
        int xPos = startX + 60;
        Nodo* actual = listaAdyacencia[i].getCabeza();
        while(actual != nullptr) {
            char adj[3];
            sprintf(adj, "%d", actual->dato);
            outtextxy(xPos, startY + i * vertSpace, adj);
            line(xPos - 15, startY + i * vertSpace + 10,
                 xPos + 5, startY + i * vertSpace + 10);
                 
            outtextxy(xPos + 10, startY + i * vertSpace, adj);
            xPos += horizSpace;
            actual = actual->siguiente;
        }
    }
}

void Grafo::dibujarGrafo() const {
    cleardevice();
    setbkcolor(BLACK);
    cleardevice();
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 50, 10, "Grafo");
    
    // Dibujar vértices
    for(int i = 0; i < numVertices; i++) {
        circle(coordX[i], coordY[i], 20);
        char label[3];
        sprintf(label, "%d", i);
        outtextxy(coordX[i] - 5, coordY[i] - 5, label);
    }
    
    // Dibujar aristas
    for(int i = 0; i < numVertices; i++) {
        for(int j = 0; j < numVertices; j++) {
            if(matrizAdyacencia[i][j]) {
                if(dirigido) {
                    // Calcular punto de flecha
                    double dx = coordX[j] - coordX[i];
                    double dy = coordY[j] - coordY[i];
                    double len = sqrt(dx*dx + dy*dy);
                    double unitX = dx/len;
                    double unitY = dy/len;
                    
                    int endX = coordX[i] + unitX * (len - 25);
                    int endY = coordY[i] + unitY * (len - 25);
                    
                    line(coordX[i], coordY[i], endX, endY);
                    
                    // Dibujar punta de flecha
                    double angle = atan2(dy, dx);
                    int arrowSize = 10;
                    line(endX, endY, 
                         endX - arrowSize * cos(angle - M_PI/6),
                         endY - arrowSize * sin(angle - M_PI/6));
                    line(endX, endY,
                         endX - arrowSize * cos(angle + M_PI/6),
                         endY - arrowSize * sin(angle + M_PI/6));
                } else {
                    if(i < j) {
                        line(coordX[i], coordY[i],
                             coordX[j], coordY[j]);
                    }
                }
            }
        }
    }
}
