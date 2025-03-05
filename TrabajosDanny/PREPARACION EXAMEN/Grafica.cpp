#include "Grafica.h"
#include <iostream>

Grafica::Grafica() {
    inicializarGraficos();
}

void Grafica::inicializarGraficos() {
    driver = DETECT;
    initgraph(&driver, &modo, "");
}

void Grafica::limpiarPantalla() {
    cleardevice();
}

void Grafica::dibujarCarro(const Carro& carro) {
    // Dibujar el cuerpo del carro
    rectangle(carro.getX(), carro.getY(), carro.getX() + 100, carro.getY() + 50);
    
    // Dibujar el techo
    line(carro.getX() + 25, carro.getY(), carro.getX() + 35, carro.getY() - 20);
    line(carro.getX() + 35, carro.getY() - 20, carro.getX() + 65, carro.getY() - 20);
    line(carro.getX() + 65, carro.getY() - 20, carro.getX() + 75, carro.getY());
    
    // Dibujar las ruedas
    circle(carro.getX() + 25, carro.getY() + 50, 10);
    circle(carro.getX() + 75, carro.getY() + 50, 10);
    
    // Actualizar la pantalla
    delay(100);
}

Grafica::~Grafica() {
    closegraph();
}