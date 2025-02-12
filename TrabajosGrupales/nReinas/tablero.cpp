#include "Tablero.h"
#include <graphics.h>
#include <iostream>

Tablero::Tablero(int size, bool animacion) : n(size), intentos(0), mostrarAnimacion(animacion) {
    tablero = new int;
    tablero = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        *(tablero + i) = -1;
    }
}

bool Tablero::resolverNReinas(int col) {
    if(col >= n)
        return true;
        
    for(int i = 0; i < n; i++) {
        if(esPosicionSegura(i, col)) {
            *(tablero + col) = i;
            intentos++;
            
            if(mostrarAnimacion && intentos % Constantes::ANIMATION_FREQUENCY == 0) {
                dibujar();
                for(int j = 0; j <= col; j++) {
                    dibujarReina(*(tablero + j), j);
                }
                delay(Constantes::ANIMATION_DELAY);
            }
        
            if(resolverNReinas(col + 1))
                return true;
                
            *(tablero + col) = -1;
        }
    }
    return false;
}

Tablero::~Tablero() {
    free(tablero);
}

void Tablero::dibujar() {
    cleardevice();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x = Constantes::MARGIN + j * Constantes::CELL_SIZE;
            int y = Constantes::MARGIN + i * Constantes::CELL_SIZE;
            
            if((i + j) % 2 == 0)
                setfillstyle(SOLID_FILL, WHITE);
            else
                setfillstyle(SOLID_FILL, BLACK);
                
            bar(x, y, x + Constantes::CELL_SIZE, y + Constantes::CELL_SIZE);
            rectangle(x, y, x + Constantes::CELL_SIZE, y + Constantes::CELL_SIZE);
        }
    }
}

void Tablero::dibujarReina(int row, int col) {
    int x = Constantes::MARGIN + col * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
    int y = Constantes::MARGIN + row * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
    
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(x, y, Constantes::CELL_SIZE/3);
    floodfill(x, y, RED);
}

bool Tablero::esPosicionSegura(int row, int col) {
    for(int i = 0; i < col; i++)
        if(*(tablero + i) == row)
            return false;
            
    for(int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if(*(tablero + j) == i)
            return false;
            
    for(int i = row, j = col; i < n && j >= 0; i++, j--)
        if(*(tablero + j) == i)
            return false;
            
    return true;
}
