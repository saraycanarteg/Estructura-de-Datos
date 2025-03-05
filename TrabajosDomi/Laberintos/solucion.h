// solucion.h
#ifndef SOLUCION_H
#define SOLUCION_H

#include <graphics.h>

class Solucion {
public:
    bool resolverLaberinto(int maze[10][10], int size, int x, int y, int endX, int endY);
private:
    bool resolverLaberintoRecursivo(int maze[10][10], int size, int x, int y, int endX, int endY, bool animacionBacktracking);
    void dibujarPaso(int x, int y, int color);
    void dibujarCaminoFinal(int x, int y);
};

#endif // SOLUCION_H