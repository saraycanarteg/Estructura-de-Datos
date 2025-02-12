#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"

class Juego {
private:
    Tablero* tablero;
    void inicializarGraficos(int n);
    bool preguntarAnimacion();

public:
    Juego();
    ~Juego();
    void iniciar();
    void mostrarResultado();
};

#endif