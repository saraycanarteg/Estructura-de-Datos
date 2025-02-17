#ifndef TABLERO_H
#define TABLERO_H

class Tablero {
private:
    int n;
    
public:
    Tablero(int size);
    void dibujar();
    void dibujarCaballo(int row, int col);
    void mostrarMovimientosPosibles(int row, int col);
    bool esMovimientoValido(int row, int col);
};

#endif