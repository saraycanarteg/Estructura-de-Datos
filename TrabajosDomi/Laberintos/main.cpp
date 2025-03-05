// main.cpp
#include <graphics.h>
#include "solucion.h"

const int MAZE_SIZE = 10;
int maze[MAZE_SIZE][MAZE_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,1,0,1,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

void dibujarLaberinto(int maze[MAZE_SIZE][MAZE_SIZE]) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (maze[i][j] == 1) {
                // Dibujar paredes en gris oscuro
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(j*50, i*50, (j+1)*50, (i+1)*50);
            } else {
                // Dibujar caminos en blanco
                setfillstyle(SOLID_FILL, WHITE);
                bar(j*50, i*50, (j+1)*50, (i+1)*50);
            }
        }
    }
}

int main() {
    // Inicializar gráficos
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Dibujar laberinto inicial
    dibujarLaberinto(maze);

    // Resolver laberinto
    Solucion solver;
    int startX = 1, startY = 1;
    int endX = 8, endY = 8;

    // Resolver con animación de backtracking
    if (solver.resolverLaberinto(maze, MAZE_SIZE, startX, startY, endX, endY)) {
        outtextxy(10, getmaxy() - 30, "Camino encontrado!");
    } else {
        outtextxy(10, getmaxy() - 30, "No hay camino.");
    }

    delay(5000);
    closegraph();
    return 0;
}