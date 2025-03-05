#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

const int MAX_VERTICES = 10;

// Arreglo de nombres de colores
const std::string NOMBRES_COLORES[] = {
    "Rojo", "Verde", "Azul", "Amarillo", 
    "Magenta", "Cyan", "Naranja", "Morado"
};

// Función para crear grafo aleatorio
void crearGrafoAleatorio(int grafo[][MAX_VERTICES], int num_vertices) {
    // Inicializar grafo sin conexiones
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            grafo[i][j] = 0;
        }
    }

    // Generar conexiones aleatorias
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            // Probabilidad de conexión del 40%
            if (rand() % 100 < 40) {
                grafo[i][j] = grafo[j][i] = 1;
            }
        }
    }
}

// Función para verificar si un color es válido
bool esColorValido(int grafo[][MAX_VERTICES], int vertice, int color, 
                   std::vector<int>& colores, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        // Verificar vértices adyacentes
        if (grafo[vertice][i] && colores[i] == color) {
            return false;
        }
    }
    return true;
}

// Función de coloreo recursivo (backtracking)
bool colorea(int grafo[][MAX_VERTICES], int num_vertices, int num_colores, 
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

// Función para imprimir grafo y coloreo
void imprimirGrafo(int grafo[][MAX_VERTICES], int num_vertices, 
                   const std::vector<int>& colores) {
    // Imprimir matriz de adyacencia
    std::cout << "\nMatriz de Adyacencia:" << std::endl;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            std::cout << grafo[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Imprimir coloreo
    std::cout << "\nColoreo de Grafo:" << std::endl;
    for (int i = 0; i < num_vertices; i++) {
        std::cout << "Vértice " << i << ": " 
                  << NOMBRES_COLORES[colores[i]-1] 
                  << " (" << colores[i] << ") - Inicial: " 
                  << NOMBRES_COLORES[colores[i]-1][0] << std::endl;
    }

    // Imprimir representación visual simple
    std::cout << "\nRepresentación simplificada:" << std::endl;
    for (int i = 0; i < num_vertices; i++) {
        char inicial = NOMBRES_COLORES[colores[i]-1][0];
        std::cout << "V" << i << "(" << inicial << ") ";
    }
    std::cout << std::endl;
}

int main() {
    // Configurar semilla aleatoria
    srand(time(NULL));

    int num_vertices, num_colores;

    // Instrucciones en consola
    std::cout << "PROBLEMA DE COLOREO DE GRAFOS" << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    // Solicitar número de vértices
    do {
        std::cout << "Ingrese el número de vértices (1-" << MAX_VERTICES << "): ";
        std::cin >> num_vertices;
    } while (num_vertices < 1 || num_vertices > MAX_VERTICES);

    // Crear grafo aleatorio
    int G[MAX_VERTICES][MAX_VERTICES];
    crearGrafoAleatorio(G, num_vertices);

    // Solicitar número de colores
    do {
        std::cout << "\nIngrese el número de colores (m) a utilizar: ";
        std::cin >> num_colores;
    } while (num_colores < 1);

    // Vector para almacenar la solución de coloreo
    std::vector<int> colores(num_vertices, 0);

    // Llamar a la función de coloreo
    if (colorea(G, num_vertices, num_colores, colores)) {
        // Imprimir resultados
        imprimirGrafo(G, num_vertices, colores);
    } else {
        std::cout << "No se encontró solución de coloreo con " 
                  << num_colores << " colores." << std::endl;
    }

    return 0;
}