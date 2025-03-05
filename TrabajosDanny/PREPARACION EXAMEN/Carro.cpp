#include "Carro.h"

Carro::Carro() : x(0), y(0), velocidad(0), color("rojo") {}

Carro::Carro(int x, int y, int vel, string col) : x(x), y(y), velocidad(vel), color(col) {}

void Carro::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Carro::setVelocidad(int vel) {
    velocidad = vel;
}

void Carro::setColor(string col) {
    color = col;
}

int Carro::getX() const {
    return x;
}

int Carro::getY() const {
    return y;
}

int Carro::getVelocidad() const {
    return velocidad;
}

string Carro::getColor() const {
    return color;
}

void Carro::moverAdelante() {
    y += velocidad;
}

void Carro::moverAtras() {
    y -= velocidad;
}