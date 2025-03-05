#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <string>

using namespace std;

class Carro {
private:
    int x, y;          // Posición del carro
    int velocidad;     // Velocidad del carro
    string color;      // Color del carro
    
public:
    Carro();          // Constructor por defecto
    Carro(int x, int y, int vel, string col);  // Constructor parametrizado
    
    // Getters y setters
    void setPosition(int newX, int newY);
    void setVelocidad(int vel);
    void setColor(string col);
    int getX() const;
    int getY() const;
    int getVelocidad() const;
    string getColor() const;
    
    // Métodos de movimiento
    void moverAdelante();
    void moverAtras();
};

#endif