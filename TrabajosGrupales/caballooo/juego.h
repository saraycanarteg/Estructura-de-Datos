#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"

class Juego {
private:
    Tablero* tablero;
    void inicializarGraficos();
    void guardarPosicion(int x, int y);

public:
    Juego();
    ~Juego();
    void iniciar();
    void esperarClic();
};

#endif