#pragma once

class Tablero {
private:
    int** grid;
    int filas;
    int columnas;
    int currentNumber;
    int currentX;
    int currentY;
    bool gameOver;
    
    bool hayColision();
    bool eliminarParejas();
    void compactarFilaFondo();

public:
    Tablero(int filas, int columnas);
    ~Tablero();
    
    void generarNuevoNumero();
    bool moverIzquierda();
    bool moverDerecha();
    void caerRapido();
    void actualizar();
    bool compactarTablero();
    void dibujar();
    
    bool isGameOver() const;
};