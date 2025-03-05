// solucion.cpp
#include "solucion.h"

// Directions: Right, Down, Left, Up
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

void Solucion::dibujarPaso(int x, int y, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(y*50+5, x*50+5, y*50+45, x*50+45);
    delay(100);
}

void Solucion::dibujarCaminoFinal(int x, int y) {
    setfillstyle(SOLID_FILL, RED);
    bar(y*50+5, x*50+5, y*50+45, x*50+45);
}

bool Solucion::resolverLaberinto(int maze[10][10], int size, int x, int y, int endX, int endY) {
    // Create a copy of the maze to mark visited cells
    int mazeCopy[10][10];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mazeCopy[i][j] = maze[i][j];
        }
    }

    // Primero hacer la animación de backtracking
    if (!resolverLaberintoRecursivo(mazeCopy, size, x, y, endX, endY, true)) {
        return false;
    }

    // Resetear el laberinto
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mazeCopy[i][j] = maze[i][j];
        }
    }

    // Luego dibujar el camino final
    resolverLaberintoRecursivo(mazeCopy, size, x, y, endX, endY, false);

    return true;
}

bool Solucion::resolverLaberintoRecursivo(int maze[10][10], int size, int x, int y, int endX, int endY, bool animacionBacktracking) {
    // Check if out of bounds
    if (x < 0 || x >= size || y < 0 || y >= size) {
        return false;
    }

    // Check if reached the end
    if (x == endX && y == endY) {
        if (!animacionBacktracking) {
            dibujarCaminoFinal(x, y);
        }
        return true;
    }

    // Check if wall or already visited
    if (maze[x][y] == 1) {
        return false;
    }

    // Mark as visited
    maze[x][y] = 1;
    
    if (animacionBacktracking) {
        dibujarPaso(x, y, GREEN);
    }

    // Try all 4 directions
    for (int k = 0; k < 4; k++) {
        int newX = x + dx[k];
        int newY = y + dy[k];

        // Recursive call
        if (resolverLaberintoRecursivo(maze, size, newX, newY, endX, endY, animacionBacktracking)) {
            if (!animacionBacktracking) {
                dibujarCaminoFinal(x, y);
            }
            return true;
        }
    }

    // Backtrack
    if (animacionBacktracking) {
        maze[x][y] = 0;
        dibujarPaso(x, y, BLUE);
    }
    return false;
}