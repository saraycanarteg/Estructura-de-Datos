#pragma once
#include "Tablero.h"

class Tetris {
private:
    Tablero tablero;
public:
    Tetris(int filas, int columnas);
    void iniciar();
};