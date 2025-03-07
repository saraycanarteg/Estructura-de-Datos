// animacion.h
#ifndef ANIMACION_H
#define ANIMACION_H

#include <graphics.h>
#include "Juego.h"

class Animacion {
private:
    Juego& juego;

public:
    Animacion(Juego& juegoRef);
    void dibujarTablero();
    void dibujarLetra(const Letra& letra);
    void dibujarMenu();
    void dibujarPuntaje();
    void mostrarGameOver();
    void dibujarLetrasTablero();
};

#endif // ANIMACION_H