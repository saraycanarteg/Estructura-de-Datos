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
    int centerX = Constantes::MARGIN + col * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
    int centerY = Constantes::MARGIN + row * Constantes::CELL_SIZE + Constantes::CELL_SIZE/2;
    
    int size = Constantes::CELL_SIZE/3;
    int x1 = centerX;
    int y1 = centerY - size;  
    int x2 = centerX - size;  
    int y2 = centerY + size;
    int x3 = centerX + size;  
    int y3 = centerY + size;
    
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    
    int points[8] = {x1, y1, x2, y2, x3, y3, x1, y1};
    fillpoly(4, points);
}

bool Tablero::esMovimientoValido(int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

void Tablero::mostrarMovimientosPosibles(int row, int col) {
    int movimientos[8][2] = {
        {-2, -1}, {-2, 1},  
        {-1, -2}, {-1, 2},  
        {1, -2}, {1, 2},    
        {2, -1}, {2, 1}     
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