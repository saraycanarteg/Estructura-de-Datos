#include "Tetris.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

Tetris::Tetris(int filas, int columnas) : tablero(filas, columnas) {}

void Tetris::iniciar() {
    DWORD ultimoTiempoCaida = GetTickCount();
    const int intervaloCaida = 500; // 500 ms (0.5 segundos) 

    while (!tablero.isGameOver()) {
        DWORD tiempoActual = GetTickCount();
        
        // Control de la caída automática
        if (tiempoActual - ultimoTiempoCaida >= intervaloCaida) {
            tablero.actualizar();
            ultimoTiempoCaida = tiempoActual;
        }

        // Control de entrada
        if (_kbhit()) {
            int tecla = _getch();
            if (tecla == 224) { // Tecla especial (flechas)
                tecla = _getch();
                switch (tecla) {
                    case 75: tablero.moverIzquierda(); break;
                    case 77: tablero.moverDerecha(); break;
                }
                tablero.dibujar(); // Actualizar visualización inmediatamente
            }
            else if (tecla == 32) { // Barra espaciadora
                tablero.caerRapido();
                tablero.dibujar(); // Actualizar visualización inmediatamente
            }
        }

        // Redibujar periódicamente
        if (tiempoActual % 100 == 0) { // Actualiza pantalla cada 100ms
            tablero.dibujar();
        }

        Sleep(10);
    }
    
    system("cls");
    std::cout << "¡Game Over!" << std::endl;
}