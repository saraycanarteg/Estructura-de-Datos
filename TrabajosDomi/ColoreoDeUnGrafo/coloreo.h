#ifndef COLOREO_H
#define COLOREO_H

#include <vector>
#include <graphics.h>
#include <cmath>

const int MAX_VERTICES = 10;  // Límite máximo de vértices

// Function prototypes
bool esColorValido(int grafo[MAX_VERTICES][MAX_VERTICES], int vertice, int color, 
                   std::vector<int>& colores, int num_vertices);

bool colorea(int grafo[MAX_VERTICES][MAX_VERTICES], int num_vertices, int num_colores, 
             std::vector<int>& colores, int vertice);

void dibujarGrafo(int grafo[MAX_VERTICES][MAX_VERTICES], int num_vertices, std::vector<int>& colores);

// Implementations (similar a la versión anterior)
bool esColorValido(int grafo[MAX_VERTICES][MAX_VERTICES], int vertice, int color, 
                   std::vector<int>& colores, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        // Verificar vértices adyacentes
        if (grafo[vertice][i] && colores[i] == color) {
            return false;
        }
    }
    return true;
}

bool colorea(int grafo[MAX_VERTICES][MAX_VERTICES], int num_vertices, int num_colores, 
             std::vector<int>& colores, int vertice = 0) {
    // Caso base: se han coloreado todos los vértices
    if (vertice == num_vertices) {
        return true;
    }

    // Probar colores para el vértice actual
    for (int color = 1; color <= num_colores; color++) {
        if (esColorValido(grafo, vertice, color, colores, num_vertices)) {
            // Asignar color
            colores[vertice] = color;

            // Recursión para siguiente vértice
            if (colorea(grafo, num_vertices, num_colores, colores, vertice + 1)) {
                return true;
            }

            // Backtracking: deshacer asignación si no funciona
            colores[vertice] = 0;
        }
    }

    return false;
}

// Función para dibujar el grafo con disposición adaptativa
void dibujarGrafo(int grafo[MAX_VERTICES][MAX_VERTICES], int num_vertices, std::vector<int>& colores) {
    // Definir colores para cada índice de color
    int color_map[] = {
        COLOR(255, 0, 0),    // Rojo
        COLOR(0, 255, 0),    // Verde
        COLOR(0, 0, 255),    // Azul
        COLOR(255, 255, 0),  // Amarillo
        COLOR(255, 0, 255),  // Magenta
        COLOR(0, 255, 255),  // Cyan
        COLOR(128, 0, 128),  // Púrpura
        COLOR(255, 165, 0),  // Naranja
        COLOR(0, 128, 0),    // Verde oscuro
        COLOR(165, 42, 42)   // Marrón
    };

    // Calcular posiciones de los vértices en un círculo
    int radio = 200;
    int centro_x = 400;
    int centro_y = 300;

    // Dibujar aristas
    setcolor(WHITE);
    for (int i = 0; i < num_vertices; i++) {
        int x1 = centro_x + radio * cos(2 * 3.14159 * i / num_vertices);
        int y1 = centro_y + radio * sin(2 * 3.14159 * i / num_vertices);

        for (int j = i+1; j < num_vertices; j++) {
            if (grafo[i][j]) {
                int x2 = centro_x + radio * cos(2 * 3.14159 * j / num_vertices);
                int y2 = centro_y + radio * sin(2 * 3.14159 * j / num_vertices);
                line(x1, y1, x2, y2);
            }
        }
    }

    // Dibujar vértices coloreados
    for (int i = 0; i < num_vertices; i++) {
        int x = centro_x + radio * cos(2 * 3.14159 * i / num_vertices);
        int y = centro_y + radio * sin(2 * 3.14159 * i / num_vertices);

        setfillstyle(SOLID_FILL, color_map[colores[i] - 1]);
        fillellipse(x, y, 30, 30);
        
        // Dibujar número de vértice
        setcolor(BLACK);
        char str[3];
        sprintf(str, "%d", i);
        outtextxy(x-5, y-5, str);
    }
}

#endif // COLOREO_H