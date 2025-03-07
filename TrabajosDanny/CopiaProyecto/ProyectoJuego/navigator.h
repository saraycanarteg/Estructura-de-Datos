#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <vector>
#include <utility>
#include <string>

class Navigator {
private:
    // Definir el tamaño del grid para navegación
    static const int GRID_ROWS = 9;
    static const int GRID_COLS = 9;
    
    // Array para almacenar el estado del grid (0 = libre, 1 = obstáculo)
    int grid[GRID_ROWS][GRID_COLS];
    
    // Posición del destino
    int destX, destY;
    
    // Posición actual del jugador
    int playerGridX, playerGridY;
    
    // Ruta óptima encontrada
    std::vector<std::pair<int, int>> path;
    
    // Funciones auxiliares para backtracking
    bool findPath(int x, int y, std::vector<std::pair<int, int>>& currentPath);
    bool isValidPosition(int x, int y);
    int convertCoordToGrid(int coord, bool isX);
    std::pair<int, int> convertGridToCoord(int gridX, int gridY);
    
public:
    Navigator();
    ~Navigator();
    
    // Inicializar el navegador con un destino
    void setDestination(int x, int y);
    
    // Actualizar la posición del jugador
    void updatePlayerPosition(int x, int y);
    
    // Actualizar el grid con obstáculos
    void updateObstacles(int obstacleX, int obstacleY);
    
    // Encontrar la mejor ruta usando backtracking
    bool calculateRoute();
    
    // Obtener la siguiente dirección recomendada
    std::pair<int, int> getNextDirection();
    
    // Dibujar el minimapa
    void drawMinimap();
    
    // Verificar si el jugador ha llegado al destino
    bool hasReachedDestination(int playerX, int playerY);
    
    // Reiniciar el navegador
    void reset();
};

#endif