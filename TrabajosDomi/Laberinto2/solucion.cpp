// solucion.cpp
#include "solucion.h"

// Definición explícita de los miembros estáticos
const int Solucion::dx[4] = {0, 1, 0, -1};
const int Solucion::dy[4] = {1, 0, -1, 0};

void Solucion::imprimirLaberinto(std::vector<std::vector<char>>& laberinto) {
    // Limpiar pantalla (método portable)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    for (const auto& fila : laberinto) {
        for (char celda : fila) {
            std::cout << celda << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    // Esperar entrada de teclado
    std::cout << "Presiona ENTER para continuar..." << std::endl;
    std::cin.get();
}

bool Solucion::resolverLaberintoRecursivo(
    std::vector<std::vector<char>>& laberinto, 
    int x, int y, 
    int endX, int endY, 
    bool buscarCamino
) {
    // Fuera de límites
    if (x < 0 || x >= laberinto.size() || 
        y < 0 || y >= laberinto[0].size()) {
        return false;
    }

    // Llegamos al final
    if (x == endX && y == endY) {
        if (!buscarCamino) {
            laberinto[x][y] = 'O';
        }
        return true;
    }

    // Pared o ya visitado
    if (laberinto[x][y] == '#' || laberinto[x][y] == '.') {
        return false;
    }

    // Marcar visitado o mostrar exploración
    char original = laberinto[x][y];
    if (buscarCamino) {
        laberinto[x][y] = '.';
        imprimirLaberinto(laberinto);
    }

    // Intentar en 4 direcciones
    for (int k = 0; k < 4; k++) {
        int newX = x + dx[k];
        int newY = y + dy[k];

        if (resolverLaberintoRecursivo(laberinto, newX, newY, endX, endY, buscarCamino)) {
            if (!buscarCamino) {
                laberinto[x][y] = 'O';
            }
            return true;
        }
    }

    // Backtracking
    if (buscarCamino) {
        laberinto[x][y] = original;
        imprimirLaberinto(laberinto);
    }

    return false;
}

bool Solucion::resolverLaberinto(
    std::vector<std::vector<char>>& laberinto, 
    int startX, int startY, 
    int endX, int endY
) {
    // Limpiar cualquier entrada previa
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Copia del laberinto para no modificar el original
    auto laberintoCopia = laberinto;

    // Primero buscar camino (con animación)
    if (!resolverLaberintoRecursivo(laberintoCopia, startX, startY, endX, endY, true)) {
        std::cout << "No hay camino." << std::endl;
        return false;
    }

    // Luego marcar camino final
    laberintoCopia = laberinto;
    resolverLaberintoRecursivo(laberintoCopia, startX, startY, endX, endY, false);

    std::cout << "Camino encontrado:" << std::endl;
    imprimirLaberinto(laberintoCopia);

    return true;
}