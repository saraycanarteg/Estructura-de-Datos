#include "Tablero.h"
#include "Constantes.h"
#include <graphics.h>

Tablero::Tablero(int size) : n(size) {}

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

void Tablero::dibujarCaballo(int row, int col) {
    int x = Constantes::MARGIN + col * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
    int y = Constantes::MARGIN + row * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
    
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    
    // Dibujar un círculo para representar el caballo
    circle(x, y, Constantes::CELL_SIZE/3);
    floodfill(x, y, RED);
}

bool Tablero::esMovimientoValido(int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

void Tablero::mostrarMovimientosPosibles(int row, int col) {
    // Movimientos posibles del caballo
    int movimientos[8][2] = {
        {-2, -1}, {-2, 1},  // Arriba
        {-1, -2}, {-1, 2},  // Izquierda y derecha arriba
        {1, -2}, {1, 2},    // Izquierda y derecha abajo
        {2, -1}, {2, 1}     // Abajo
    };
    
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    
    for(int i = 0; i < 8; i++) {
        int nuevaFila = row + movimientos[i][0];
        int nuevaCol = col + movimientos[i][1];
        
        if(esMovimientoValido(nuevaFila, nuevaCol)) {
            int x = Constantes::MARGIN + nuevaCol * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
            int y = Constantes::MARGIN + nuevaFila * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
            
            circle(x, y, Constantes::CELL_SIZE/4);
            floodfill(x, y, GREEN);
        }
    }
}