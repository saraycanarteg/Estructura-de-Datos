// solucion.h
#ifndef SOLUCION_H
#define SOLUCION_H

#include <vector>
#include <iostream>
#include <limits>
#include <cstdlib>

class Solucion {
private:
    // Direcciones de movimiento: derecha, abajo, izquierda, arriba
    static const int dx[4];
    static const int dy[4];
    
    // Método privado para imprimir el estado actual del laberinto
    void imprimirLaberinto(std::vector<std::vector<char>>& laberinto);
    
    // Método recursivo de backtracking para resolver el laberinto
    bool resolverLaberintoRecursivo(
        std::vector<std::vector<char>>& laberinto, 
        int x, int y, 
        int endX, int endY, 
        bool buscarCamino
    );

public:
    // Método público para iniciar la resolución del laberinto
    bool resolverLaberinto(
        std::vector<std::vector<char>>& laberinto, 
        int startX, int startY, 
        int endX, int endY
    );
};

#endif // SOLUCION_H