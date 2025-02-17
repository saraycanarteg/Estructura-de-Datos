#ifndef NREINAS_H
#define NREINAS_H

#include <iostream>
#include <graphics.h>

using namespace std;

class NReinas {
private:
    int n;
    int* tablero;

public:
    NReinas(int size);
    ~NReinas();
    bool esSeguro(int fila, int col);
    bool resolverNReinas(int col);
    void mostrarTablero();
    void resolver();
};

#endif