#include "Crossroad.h"
#include <graphics.h>

// Definición de constantes de color
#define WHITE 15

// Constructor
Crossroad::Crossroad() {
    // No necesita inicialización específica
}

// Destructor
Crossroad::~Crossroad() {
    // No necesita realizar acciones específicas
}

// Función para dibujar el cruce
void Crossroad::draw() const {
    // Fondo gris para las calles
    setcolor(8); // Gris oscuro
    setfillstyle(SOLID_FILL, 8);
    
    // Calles horizontales (3 calles)
    bar(0, 120, 640, 180);  // Calle superior
    bar(0, 220, 640, 280);  // Calle central
    bar(0, 320, 640, 380);  // Calle inferior
    
    // Calles verticales (3 calles)
    bar(120, 0, 180, 480);  // Calle izquierda
    bar(220, 0, 280, 480);  // Calle central
    bar(320, 0, 380, 480);  // Calle derecha
    
    // Líneas blancas divisorias
    setcolor(WHITE);
    setlinestyle(DASHED_LINE, 0, 1);
    
    // Líneas horizontales
    for(int y = 150; y <= 350; y += 100) {
        for(int x = 0; x < 640; x += 200) {
            if(x < 120 || (x > 180 && x < 220) || (x > 280 && x < 320) || x > 380) {
                line(x, y, x + 100, y);
            }
        }
    }
    
    // Líneas verticales
    for(int x = 150; x <= 350; x += 100) {
        for(int y = 0; y < 480; y += 200) {
            if(y < 120 || (y > 180 && y < 220) || (y > 280 && y < 320) || y > 380) {
                line(x, y, x, y + 100);
            }
        }
    }
    
    setlinestyle(SOLID_LINE, 0, 1);
}