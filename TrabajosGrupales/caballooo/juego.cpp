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

void Juego::guardarPosicion(int x, int y) {
    ofstream archivo("posiciones.txt", ios::app);
    if(archivo.is_open()) {
        archivo << "Posición del caballo: (" << x + 1 << "," << y + 1 << ")\n";
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
            
            // Convertir coordenadas del clic a posición del tablero
            int columna = (x - Constantes::MARGIN) / Constantes::CELL_SIZE;
            int fila = (y - Constantes::MARGIN) / Constantes::CELL_SIZE;
            
            if(columna >= 0 && columna < 8 && fila >= 0 && fila < 8) {
                tablero->dibujar(); // Limpiar tablero
                tablero->dibujarCaballo(fila, columna);
                tablero->mostrarMovimientosPosibles(fila, columna);
                guardarPosicion(fila, columna);
            }
        }
        if(kbhit() && getch() == 27) // ESC para salir
            break;
    }
}