#include "Tablero.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <WINDOWS.H>

Tablero::Tablero(int filas, int columnas) : filas(filas), columnas(columnas), gameOver(false) {
    grid = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        grid[i] = new int[columnas]();
    }
    currentNumber = 0;
    currentX = columnas / 2;
    currentY = 0;
    generarNuevoNumero();
    srand(time(NULL));
}

Tablero::~Tablero() {
    for (int i = 0; i < filas; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Tablero::generarNuevoNumero() {
    currentNumber = rand() % 9 + 1;
    currentX = columnas / 2;
    currentY = 0;
    
    if (grid[currentY][currentX] != 0) {
        gameOver = true;
    }
}

bool Tablero::moverIzquierda() {
    if (currentX > 0 && grid[currentY][currentX - 1] == 0) {
        currentX--;
        return true;
    }
    return false;
}

bool Tablero::moverDerecha() {
    if (currentX < columnas - 1 && grid[currentY][currentX + 1] == 0) {
        currentX++;
        return true;
    }
    return false;
}

void Tablero::caerRapido() {
    while (!hayColision()) {
        currentY++;
    }
}

bool Tablero::hayColision() {
    return (currentY + 1 >= filas) || (grid[currentY + 1][currentX] != 0);
}

void Tablero::compactarFilaFondo() {
    int* filaFondo = grid[filas - 1];
    int indiceEscritura = 0;
    
    // Primero movemos todos los números a la izquierda
    for (int j = 0; j < columnas; ++j) {
        if (filaFondo[j] != 0) {
            if (indiceEscritura != j) {
                filaFondo[indiceEscritura] = filaFondo[j];
                filaFondo[j] = 0;
            }
            indiceEscritura++;
        }
    }
}

bool Tablero::compactarTablero() {
    bool huboCompactacion = false;
    
    // Compactación vertical
    for (int j = 0; j < columnas; ++j) {
        int writeRow = filas - 1;
        for (int i = filas - 1; i >= 0; --i) {
            if (grid[i][j] != 0) {
                if (writeRow != i) {
                    grid[writeRow][j] = grid[i][j];
                    grid[i][j] = 0;
                    huboCompactacion = true;
                }
                writeRow--;
            }
        }
    }
    
    // Compactación horizontal y detección de cambios
    int* copiaFila = new int[columnas];
    std::copy(grid[filas - 1], grid[filas - 1] + columnas, copiaFila);
    
    compactarFilaFondo();
    
    if (!std::equal(grid[filas - 1], grid[filas - 1] + columnas, copiaFila)) {
        huboCompactacion = true;
    }
    delete[] copiaFila;
    
    return huboCompactacion;
}

void Tablero::actualizar() {
    if (gameOver) return;
    
    if (hayColision()) {
        grid[currentY][currentX] = currentNumber;
        
        bool huboEliminacion;
        bool huboCompactacion;
        do {
            huboEliminacion = eliminarParejas();
            huboCompactacion = compactarTablero();
        } while (huboEliminacion || huboCompactacion);
        
        generarNuevoNumero();
    } else {
        currentY++;
    }
}

bool Tablero::eliminarParejas() {
    bool** eliminar = new bool*[filas];
    for (int i = 0; i < filas; ++i) {
        eliminar[i] = new bool[columnas]();
    }
    
    bool eliminaciones = false;
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (grid[i][j] == 0) continue;
            
            if (j < columnas - 1 && grid[i][j] == grid[i][j + 1]) {
                eliminar[i][j] = true;
                eliminar[i][j + 1] = true;
                eliminaciones = true;
            }
            if (i < filas - 1 && grid[i][j] == grid[i + 1][j]) {
                eliminar[i][j] = true;
                eliminar[i + 1][j] = true;
                eliminaciones = true;
            }
        }
    }
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (eliminar[i][j]) grid[i][j] = 0;
        }
    }
    
    for (int i = 0; i < filas; ++i) delete[] eliminar[i];
    delete[] eliminar;
    
    return eliminaciones;
}

void Tablero::dibujar() {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Configurar color según el número
            auto setColor = [&hConsole](int num) {
                const int colores[] = {
                    0x07, // Gris
                    0x0A, // 1 Verde
                    0x0C, // 2 Rojo
                    0x0B, // 3 Cyan
                    0x09, // 4 Azul
                    0x0E, // 5 Amarillo
                    0x0D, // 6 Magenta
                    0x04, // 7 Vermillon
                    0x02, // 8 Verde oscuro
                    0x03  // 9 Celeste
                };
                SetConsoleTextAttribute(hConsole, colores[num]);
            };

            if (i == currentY && j == currentX) {
                SetConsoleTextAttribute(hConsole, 0x0F);
                std::cout << currentNumber << " ";
            } else if (grid[i][j] == 0) {
                setColor(0);
                std::cout << ". ";
            } else {
                setColor(grid[i][j]);
                std::cout << grid[i][j] << " ";
            }
        }
        SetConsoleTextAttribute(hConsole, 0x07); // Resetear color
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(hConsole, 0x07); // Restaurar color
}

bool Tablero::isGameOver() const {
    return gameOver;
}