#include "Juego.h"
#include "Constantes.h"
#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <fstream>
using namespace std;

Juego::Juego() : tablero(nullptr) {}

Juego::~Juego() {
    if(tablero != nullptr) {
        delete tablero;
    }
}

void Juego::inicializarGraficos() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    int windowWidth = 2 * Constantes::MARGIN + 8 * Constantes::CELL_SIZE;
    int windowHeight = 2 * Constantes::MARGIN + 8 * Constantes::CELL_SIZE;
    
    initwindow(windowWidth, windowHeight, "Movimientos del Caballo");
}

void Juego::guardarPosicion(int row, int col) {
    char board[8][8];
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = ' '; 
        }
    }
 
    board[row][col] = 'C';

    int movimientos[8][2] = {
        {-2, -1}, {-2, 1},  
        {-1, -2}, {-1, 2},  
        {1, -2}, {1, 2},    
        {2, -1}, {2, 1}     
    };
    
    for(int i = 0; i < 8; i++) {
        int nuevaFila = row + movimientos[i][0];
        int nuevaCol = col + movimientos[i][1];
        
        if(tablero->esMovimientoValido(nuevaFila, nuevaCol)) {
            board[nuevaFila][nuevaCol] = 'O';
        }
    }
    
    ofstream archivo("posiciones.txt", ios::app);
    if(archivo.is_open()) {
        archivo << "\nNueva posición del caballo en: (" << row + 1 << "," << col + 1 << ")\n\n";
        
        archivo << "    1   2   3   4   5   6   7   8\n";
        
        archivo << "  ---------------------------------\n";
        
        for(int i = 0; i < 8; i++) {
            archivo << i + 1 << " "; 
            for(int j = 0; j < 8; j++) {
                archivo << "| " << board[i][j] << " ";
            }
            archivo << "|\n";  
            archivo << "  ---------------------------------\n";  
        }
        
        archivo << "\nLeyenda:\n";
        archivo << "C: Posición actual del caballo\n";
        archivo << "O: Movimientos posibles\n";
        archivo << "----------------------------------------\n";
        
        archivo.close();
    }
}

void Juego::iniciar() {
    inicializarGraficos();
    tablero = new Tablero(8);
    tablero->dibujar();
    esperarClic();
}

void Juego::esperarClic() {
    int x, y;
    while(true) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            
            int columna = (x - Constantes::MARGIN) / Constantes::CELL_SIZE;
            int fila = (y - Constantes::MARGIN) / Constantes::CELL_SIZE;
            
            if(columna >= 0 && columna < 8 && fila >= 0 && fila < 8) {
                tablero->dibujar(); 
                tablero->dibujarCaballo(fila, columna);
                tablero->mostrarMovimientosPosibles(fila, columna);
                guardarPosicion(fila, columna);
            }
        }
        if(kbhit() && getch() == 27) 
            break;
    }
}