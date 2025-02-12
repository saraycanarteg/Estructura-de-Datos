#ifndef TABLERO_H
#define TABLERO_H

#include "Constantes.h"

class Tablero {
private:
    int n;
    int* tablero;
    int intentos;
    bool mostrarAnimacion;

public:
    Tablero(int size, bool animacion = true);
    ~Tablero();
    void dibujar();
    void dibujarReina(int row, int col);
    bool esPosicionSegura(int row, int col);
    bool resolverNReinas(int col);
    int getTamanio() { return n; }
    int* getTablero() { return tablero; }
    void setMostrarAnimacion(bool valor) { mostrarAnimacion = valor; }
};

#endif