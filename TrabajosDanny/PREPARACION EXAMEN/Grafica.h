#ifndef GRAFICA_H
#define GRAFICA_H

#include "Carro.h"
#include <graphics.h>

class Grafica {
private:
    int driver, modo;
    
public:
    Grafica();
    void inicializarGraficos();
    void dibujarCarro(const Carro& carro);
    void limpiarPantalla();
    ~Grafica();
};

#endif