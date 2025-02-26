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
    
    // Calle horizontal
    bar(0, 220, 640, 280);
    // Calle vertical
    bar(220, 0, 280, 480);
    
    // Líneas blancas de las calles
    setcolor(WHITE);
    setlinestyle(DASHED_LINE, 0, 1);
    
    // Líneas horizontales
    line(0, 250, 220, 250);
    line(280, 250, 640, 250);
    
    // Líneas verticales
    line(250, 0, 250, 220);
    line(250, 280, 250, 480);
    
    // Volver al estilo de línea normal
    setlinestyle(SOLID_LINE, 0, 1);
}