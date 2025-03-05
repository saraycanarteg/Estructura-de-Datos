// main.cpp
#include "solucion.h"

int main() {
    // Definir laberinto
    std::vector<std::vector<char>> laberinto = {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ','#','#','#','#','#','#',' ','#'},
        {'#',' ','#',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ','#',' ','#','#','#','#',' ','#'},
        {'#',' ',' ',' ',' ',' ','#',' ',' ','#'},
        {'#',' ','#','#','#',' ','#',' ','#','#'},
        {'#',' ',' ',' ','#',' ',' ',' ',' ','#'},
        {'#',' ','#',' ',' ',' ','#','#',' ','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };

    // Marcar inicio (S) y final (E)
    int startX = 1, startY = 1;
    int endX = 8, endY = 8;
    laberinto[startX][startY] = 'S';  // Inicio
    laberinto[endX][endY] = 'E';      // Final

    // Resolver laberinto
    Solucion solver;
    solver.resolverLaberinto(laberinto, startX, startY, endX, endY);

    return 0;
}