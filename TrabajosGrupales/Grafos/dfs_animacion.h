#ifndef DFS_ANIMACION_H
#define DFS_ANIMACION_H

#include "grafo.h"
#include <stack>
#include <graphics.h>

enum class Estado {
    NO_VISITADO,
    EN_PROCESO,
    VISITADO
};

class DFSAnimacion {
private:
    static const int DELAY_MS = 1000;
    static const int STACK_START_X = 650;
    static const int STACK_START_Y = 100;
    static const int STACK_ELEMENT_HEIGHT = 40;
    
    Estado* estados;
    std::stack<int> pila;
    Grafo* grafoBase;
    
    double* coordenadasX;
    double* coordenadasY;
    bool esDirigido;
    int** matrizAdy;
    int numVertices;
    
    const int COLOR_NO_VISITADO = WHITE;
    const int COLOR_EN_PROCESO = YELLOW;
    const int COLOR_VISITADO = GREEN;
    const int COLOR_ARISTA_ARBOL = BLUE;
    const int COLOR_ARISTA_NORMAL = WHITE;
    
    void dibujarPila();
    void actualizarVertice(int v, Estado nuevoEstado);
    void actualizarArista(int origen, int destino, bool esArbolDFS);
    void dfsRecursivo(int v);

public:
    DFSAnimacion(Grafo* g);
    ~DFSAnimacion();
    void ejecutarDFS(int inicio);
};

#endif