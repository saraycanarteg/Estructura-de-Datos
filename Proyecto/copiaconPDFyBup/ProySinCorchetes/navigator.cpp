#include <graphics.h>
#include <algorithm>
#include <cmath>
#include "Navigator.h"

// Definición de constantes de color
#define RED 4
#define GREEN 2
#define YELLOW 14
#define WHITE 15
#define BLACK 0
#define LIGHTBLUE 9
#define LIGHTGREEN 10

Navigator::Navigator() {
    // Inicializar el grid con memoria dinámica
    grid = new int*[GRID_ROWS];
    for (int i = 0; i < GRID_ROWS; i++) {
        grid[i] = new int[GRID_COLS];
        for (int j = 0; j < GRID_COLS; j++) {
            // Marcar como libre (0) inicialmente
            grid[i][j] = 0;
            
            // Marcar las celdas que no son calles como obstáculos (1)
            bool isHorizontalRoad = (i == 2 || i == 4 || i == 6);
            bool isVerticalRoad = (j == 2 || j == 4 || j == 6);
            
            if (!isHorizontalRoad && !isVerticalRoad) {
                grid[i][j] = 1;
            }
        }
    }
    
    // Inicializar con valores por defecto
    destX = 350;
    destY = 350;
    playerGridX = 4;
    playerGridY = 4;
}

Navigator::~Navigator() {
    // Liberar la memoria dinámica del grid
    for (int i = 0; i < GRID_ROWS; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Navigator::setDestination(int x, int y) {
    // Convertir coordenadas de pantalla a grid
    int gridX = convertCoordToGrid(x, true);
    int gridY = convertCoordToGrid(y, false);
    
    // Asegurarse de que el destino esté en una celda válida y libre
    if (gridX >= 0 && gridX < GRID_COLS && gridY >= 0 && gridY < GRID_ROWS && grid[gridY][gridX] == 0) {
        // Eliminar el destino anterior si existe
        for (int i = 0; i < GRID_ROWS; i++) {
            for (int j = 0; j < GRID_COLS; j++) {
                if (grid[i][j] == 2) {
                    grid[i][j] = 0;
                }
            }
        }
        destX = x;
        destY = y;
        grid[gridY][gridX] = 2; // Marcar como destino
    }
}

void Navigator::updatePlayerPosition(int x, int y) {
    playerGridX = convertCoordToGrid(x, true);
    playerGridY = convertCoordToGrid(y, false);
}

void Navigator::updateObstacles(int obstacleX, int obstacleY) {
    int gridX = convertCoordToGrid(obstacleX, true);
    int gridY = convertCoordToGrid(obstacleY, false);
    
    if (gridX >= 0 && gridX < GRID_COLS && gridY >= 0 && gridY < GRID_ROWS) {
        grid[gridY][gridX] = 1; // Marcar como obstáculo
    }
}

bool Navigator::calculateRoute() {
    // Limpiar la ruta anterior
    path.clear();
    
    // Iniciar con la posición actual del jugador
    std::vector<std::pair<int, int>> currentPath;
    currentPath.push_back(std::make_pair(playerGridX, playerGridY));
    
    // Realizar backtracking para encontrar la ruta
    bool found = findPath(playerGridX, playerGridY, currentPath);
    
    if (found) {
        path = currentPath;
    }
    
    return found;
}

bool Navigator::findPath(int x, int y, std::vector<std::pair<int, int>>& currentPath) {
    // Si hemos llegado al destino
    int destGridX = convertCoordToGrid(destX, true);
    int destGridY = convertCoordToGrid(destY, false);
    
    if (x == destGridX && y == destGridY) {
        return true;
    }
    
    // Direcciones posibles: arriba, derecha, abajo, izquierda
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        
        // Verificar si la nueva posición es válida
        if (isValidPosition(newX, newY)) {
            // Verificar si este punto ya está en el camino actual
            std::pair<int, int> newPos(newX, newY);
            if (std::find(currentPath.begin(), currentPath.end(), newPos) == currentPath.end()) {
                // Añadir al camino actual
                currentPath.push_back(newPos);
                
                // Intentar desde esta nueva posición
                if (findPath(newX, newY, currentPath)) {
                    return true;
                }
                
                // Si no funciona, retroceder (backtrack)
                currentPath.pop_back();
            }
        }
    }
    
    return false;
}

bool Navigator::isValidPosition(int x, int y) {
    // Verificar límites del grid
    if (x < 0 || x >= GRID_COLS || y < 0 || y >= GRID_ROWS) {
        return false;
    }
    
    // Verificar si es un obstáculo
    if (grid[y][x] == 1) {
        return false;
    }
    
    return true;
}

int Navigator::convertCoordToGrid(int coord, bool isX) {
    // Conversión de coordenadas de pantalla a grid
    if (isX) {
        // Convertir coordenada X
        if (coord < 100) return 0;
        if (coord < 200) return 2;
        if (coord < 300) return 4;
        if (coord < 400) return 6;
        return 8;
    } else {
        // Convertir coordenada Y
        if (coord < 100) return 0;
        if (coord < 200) return 2;
        if (coord < 300) return 4;
        if (coord < 400) return 6;
        return 8;
    }
}

std::pair<int, int> Navigator::convertGridToCoord(int gridX, int gridY) {
    // Convertir coordenadas de grid a pantalla
    int screenX = 50 + gridX * 50;
    int screenY = 50 + gridY * 50;
    
    return std::make_pair(screenX, screenY);
}

std::pair<int, int> Navigator::getNextDirection() {
    if (path.size() < 2) {
        return std::make_pair(0, 0); // No hay dirección disponible
    }
    
    // Obtener la siguiente posición en el camino
    std::pair<int, int> current = path[0];
    std::pair<int, int> next = path[1];
    
    // Calcular dirección
    int dx = next.first - current.first;
    int dy = next.second - current.second;
    
    // Normalizar
    if (dx != 0) dx = dx / abs(dx);
    if (dy != 0) dy = dy / abs(dy);
    
    return std::make_pair(dx, dy);
}

void Navigator::drawMinimap() {
    int minimapWidth = 150;  // Reducido de 180
    int minimapHeight = 150; // Reducido de 180
    int startX = 480;        // Ajustado para mantenerlo a la derecha
    int startY = 10;
    // Dibujar fondo del minimapa
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(startX, startY, startX + minimapWidth, startY + minimapHeight);
    
    setcolor(WHITE);
    rectangle(startX, startY, startX + minimapWidth, startY + minimapHeight);
    
    // Tamaño de cada celda en el minimapa
    int cellSize = 15;

    // Desplazamiento para centrar el grid
    int offsetX = startX + 10;
    int offsetY = startY + 10;
    
    // Dibujar grid
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            int x = offsetX + j * cellSize;
            int y = offsetY + i * cellSize;
            
            if (grid[i][j] == 1) {
                // Obstáculo
                setfillstyle(SOLID_FILL, RED);
                bar(x, y, x + cellSize - 1, y + cellSize - 1);
            } else {
                // Camino disponible
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(x, y, x + cellSize - 1, y + cellSize - 1);
            }
            
        }
    }
    
    // Dibujar destino
    int destGridX = convertCoordToGrid(destX, true);
    int destGridY = convertCoordToGrid(destY, false);
    int destMinimapX = offsetX + destGridX * cellSize;
    int destMinimapY = offsetY + destGridY * cellSize;
    
    setfillstyle(SOLID_FILL, YELLOW);
    bar(destMinimapX, destMinimapY, destMinimapX + cellSize - 1, destMinimapY + cellSize - 1);
    
    setcolor(BLACK);
    line(destMinimapX + cellSize/2, destMinimapY + cellSize - 1, 
         destMinimapX + cellSize/2, destMinimapY + cellSize/4);
    setfillstyle(SOLID_FILL, RED);
    int flagPoints[6] = {
        destMinimapX + cellSize/2, destMinimapY + cellSize/4,
        destMinimapX + cellSize - 2, destMinimapY + cellSize/3,
        destMinimapX + cellSize/2, destMinimapY + cellSize/2
    };
    fillpoly(3, flagPoints);

    // Dibujar la ruta óptima
    if (!path.empty()) {
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, LIGHTGREEN);
        
        for (size_t i = 0; i < path.size(); i++) {
            int pathX = offsetX + path[i].first * cellSize;
            int pathY = offsetY + path[i].second * cellSize;
            
            // No dibujar el punto actual del jugador como parte de la ruta
            if (i != 0) {
                fillellipse(pathX + cellSize/2, pathY + cellSize/2, cellSize/4, cellSize/4);
            }
        }
    }
    
    // Dibujar posición actual del jugador
    int playerMinimapX = offsetX + playerGridX * cellSize;
    int playerMinimapY = offsetY + playerGridY * cellSize;
    
    setcolor(WHITE);
    circle(playerMinimapX + cellSize/2, playerMinimapY + cellSize/2, cellSize/2);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(playerMinimapX + cellSize/2, playerMinimapY + cellSize/2, cellSize/2 - 1, cellSize/2 - 1);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(startX + 10, startY + minimapHeight - 20, (char*)"Verde: Tú");
    outtextxy(startX + 80, startY + minimapHeight - 20, (char*)"Rojo: Meta");

}

bool Navigator::hasReachedDestination(int playerX, int playerY) {
    // Convertir coordenadas del jugador a grid
    int gridX = convertCoordToGrid(playerX, true);
    int gridY = convertCoordToGrid(playerY, false);
    
    // Convertir coordenadas del destino a grid
    int destGridX = convertCoordToGrid(destX, true);
    int destGridY = convertCoordToGrid(destY, false);
    
    // Verificar si están en la misma celda
    return (gridX == destGridX && gridY == destGridY);
}

void Navigator::reset() {
    // Restablecer el grid
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            // Marcar como libre (0) inicialmente
            grid[i][j] = 0;
            
            // Marcar las celdas que no son calles como obstáculos (1)
            bool isHorizontalRoad = (i == 2 || i == 4 || i == 6);
            bool isVerticalRoad = (j == 2 || j == 4 || j == 6);
            
            if (!isHorizontalRoad && !isVerticalRoad) {
                grid[i][j] = 1;
            }
        }
    }
    
    // Limpiar la ruta
    path.clear();
}