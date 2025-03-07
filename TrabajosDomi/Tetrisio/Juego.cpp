#include "Juego.h"
#include <cstdlib>
#include <ctime>

Letra::Letra() : valor('A'), posX(ANCHO_TABLERO / 2), posY(0) {}

Letra::Letra(char letra) : valor(letra), posX(ANCHO_TABLERO / 2), posY(0) {}

Letra::Letra(char letra, int x, int y) : valor(letra), posX(x), posY(y) {}

void Letra::establecerValor(char letra) {
    valor = letra;
}

char Letra::obtenerValor() const {
    return valor;
}

void Letra::moverAbajo() {
    posY++;
}

void Letra::moverIzquierda() {
    posX--;
}

void Letra::moverDerecha() {
    posX++;
}

void Letra::establecerPosX(int x) {
    posX = x;
}

void Letra::establecerPosY(int y) {
    posY = y;
}

int Letra::obtenerPosX() const {
    return posX;
}

int Letra::obtenerPosY() const {
    return posY;
}

// Implementación de Tablero
Tablero::Tablero() : anchura(ANCHO_TABLERO), altura(ALTO_TABLERO) {
    limpiarTablero();
}

void Tablero::limpiarTablero() {
    for(int i = 0; i < altura; i++) {
        for(int j = 0; j < anchura; j++) {
            matriz[i][j] = nullptr;
        }
    }
}

Tablero::~Tablero() {
    for(int i = 0; i < altura; i++) {
        for(int j = 0; j < anchura; j++) {
            delete matriz[i][j];
        }
    }
}

bool Tablero::verificarColision(const Letra& letra) {
    int x = letra.obtenerPosX();
    int y = letra.obtenerPosY();

    // Verificar límites del tablero
    if(y >= altura || x < 0 || x >= anchura) return true;

    // Verificar colisión con otras letras
    if(y + 1 < altura && matriz[y + 1][x] != nullptr) {
        // Si hay una letra igual, marcar para eliminación
        if(matriz[y + 1][x]->obtenerValor() == letra.obtenerValor()) {
            return true;  // Colisión con letra igual
        }
        return true;  // Colisión con cualquier letra
    }

    return false;
}

void Tablero::insertarLetra(const Letra& letra) {
    int x = letra.obtenerPosX();
    int y = letra.obtenerPosY();
    
    // Insertar letra en la posición específica
    matriz[y][x] = new Letra(letra);

    // Eliminar letras iguales en todas las direcciones
    std::vector<std::pair<int, int>> direcciones = {
        {0, 1},   // Abajo
        {1, 0},   // Derecha
        {-1, 0},  // Izquierda
        {0, -1}   // Arriba
    };

    for(const auto& dir : direcciones) {
        int dx = dir.first;
        int dy = dir.second;
        
        // Buscar grupos de 3 letras consecutivas
        int consecutivas = 1;
        std::vector<std::pair<int, int>> posicionesEliminar;
        posicionesEliminar.push_back({x, y});
        
        // Buscar hacia una dirección
        for(int i = 1; i <= 2; i++) {
            int newX = x + dx * i;
            int newY = y + dy * i;
            
            if(newX >= 0 && newX < anchura && newY >= 0 && newY < altura &&
               matriz[newY][newX] && 
               matriz[newY][newX]->obtenerValor() == letra.obtenerValor()) {
                consecutivas++;
                posicionesEliminar.push_back({newX, newY});
            } else {
                break;
            }
        }
        
        // Eliminar grupo de 3 o más letras iguales
        if(consecutivas >= 3) {
            for(const auto& pos : posicionesEliminar) {
                delete matriz[pos.second][pos.first];
                matriz[pos.second][pos.first] = nullptr;
            }
        }
    }
}

void Tablero::eliminarLetrasIguales(int fila, char letra) {
    bool modificado = true;
    
    while(modificado) {
        modificado = false;
        
        // Verificar eliminación horizontal
        for(int j = 0; j < anchura - 2; j++) {
            if(matriz[fila][j] && matriz[fila][j+1] && matriz[fila][j+2] &&
               matriz[fila][j]->obtenerValor() == letra && 
               matriz[fila][j+1]->obtenerValor() == letra &&
               matriz[fila][j+2]->obtenerValor() == letra) {
                
                // Eliminar las tres letras iguales
                delete matriz[fila][j];
                delete matriz[fila][j+1];
                delete matriz[fila][j+2];
                matriz[fila][j] = nullptr;
                matriz[fila][j+1] = nullptr;
                matriz[fila][j+2] = nullptr;
                
                modificado = true;
            }
        }
        
        // Verificar eliminación vertical
        for(int i = 0; i < altura - 2; i++) {
            if(matriz[i][fila] && matriz[i+1][fila] && matriz[i+2][fila] &&
               matriz[i][fila]->obtenerValor() == letra && 
               matriz[i+1][fila]->obtenerValor() == letra &&
               matriz[i+2][fila]->obtenerValor() == letra) {
                
                // Eliminar las tres letras iguales verticalmente
                delete matriz[i][fila];
                delete matriz[i+1][fila];
                delete matriz[i+2][fila];
                matriz[i][fila] = nullptr;
                matriz[i+1][fila] = nullptr;
                matriz[i+2][fila] = nullptr;
                
                modificado = true;
            }
        }
        
        // Desplazar letras horizontalmente
        for(int j = 0; j < anchura - 1; j++) {
            if(matriz[fila][j] == nullptr && matriz[fila][j+1] != nullptr) {
                matriz[fila][j] = matriz[fila][j+1];
                matriz[fila][j+1] = nullptr;
            }
        }
    }
}

bool Tablero::verificarLineaCompleta(int fila) {
    for(int j = 0; j < anchura; j++) {
        if(matriz[fila][j] == nullptr) return false;
    }
    return true;
}

void Tablero::eliminarFila(int fila) {
    for(int j = 0; j < anchura; j++) {
        delete matriz[fila][j];
        matriz[fila][j] = nullptr;
    }

    // Desplazar filas hacia abajo
    for(int i = fila; i > 0; i--) {
        for(int j = 0; j < anchura; j++) {
            matriz[i][j] = matriz[i-1][j];
        }
    }
}

Letra* Tablero::obtenerLetra(int x, int y) const {
    return matriz[y][x];
}

// Implementación de Juego
Juego::Juego() : puntaje(0), nombreJugador("") {
    srand(time(nullptr));
    generarNuevaLetra();
}

void Juego::iniciarJuego() {
    // Lógica principal del juego
    generarNuevaLetra();
}

void Juego::procesarTecla(int tecla) {
    switch(tecla) {
        case 75:  // Flecha izquierda
            if(!tablero.verificarColision(Letra(letraActual.obtenerValor(), 
                                                letraActual.obtenerPosX() - 1, 
                                                letraActual.obtenerPosY())))
                letraActual.moverIzquierda();
            break;
        
        case 77:  // Flecha derecha
            if(!tablero.verificarColision(Letra(letraActual.obtenerValor(), 
                                                letraActual.obtenerPosX() + 1, 
                                                letraActual.obtenerPosY())))
                letraActual.moverDerecha();
            break;
        
        case 80:  // Flecha abajo (caída rápida)
            if(!tablero.verificarColision(Letra(letraActual.obtenerValor(), 
                                                letraActual.obtenerPosX(), 
                                                letraActual.obtenerPosY() + 1)))
                letraActual.moverAbajo();
            break;
        
        case 32:  // Espacio (colocar letra)
            // Caer directamente en la misma columna
            int columnaOriginal = letraActual.obtenerPosX();
            while(!tablero.verificarColision(Letra(letraActual.obtenerValor(), 
                                                   columnaOriginal, 
                                                   letraActual.obtenerPosY() + 1))) {
                letraActual.establecerPosX(columnaOriginal);  // Mantener columna fija
                letraActual.moverAbajo();
            }
            
            // Asegurar que la letra se inserte en la columna original
            letraActual.establecerPosX(columnaOriginal);
            
            // Insertar letra
            tablero.insertarLetra(letraActual);
            
            // Verificar si hay que eliminar filas
            for(int i = ALTO_TABLERO - 1; i >= 0; i--) {
                if(tablero.verificarLineaCompleta(i)) {
                    tablero.eliminarFila(i);
                    puntaje += 10;
                }
            }
            
            // Generar nueva letra
            generarNuevaLetra();
            break;
    }
}

bool Juego::verificarFinJuego() {
    // Si la primera fila tiene letras, termina el juego
    for(int j = 0; j < ANCHO_TABLERO; j++) {
        if(tablero.obtenerLetra(j, 0) != nullptr) {
            return true;
        }
    }
    return false;
}

int Juego::obtenerPuntaje() const {
    return puntaje;
}

void Juego::generarNuevaLetra() {
    letraActual = Letra('A' + rand() % 26);
    letraActual.establecerPosX(ANCHO_TABLERO / 2);  // Centrar inicialmente
    letraActual.establecerPosY(0);
}

Letra Juego::obtenerLetraActual() const {
    return letraActual;
}