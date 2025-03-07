#include <graphics.h>
#include "TrafficLight.h"

// Definición de constantes de color
#define RED 4
#define GREEN 2
#define YELLOW 14
#define BLACK 0

// Constructor
TrafficLight::TrafficLight(int x, int y, int direction) {
    this->x = x;
    this->y = y;
    this->state = RED;    // Estado inicial
    this->timer = 100;    // Temporizador inicial
    this->direction = direction;
}

// Destructor
TrafficLight::~TrafficLight() {
    // No necesita realizar acciones específicas
}

// Getters
int TrafficLight::getX() const {
    return x;
}

int TrafficLight::getY() const {
    return y;
}

int TrafficLight::getState() const {
    return state;
}

int TrafficLight::getDirection() const {
    return direction;
}

// Setters
void TrafficLight::setState(int state) {
    this->state = state;
}

void TrafficLight::setTimer(int timer) {
    this->timer = timer;
}

// Comportamiento
void TrafficLight::update() {
    timer--;
    if(timer <= 0) {
        switch(state) {
            case GREEN:
                state = YELLOW;
                timer = 100;  // 3 segundos para amarillo (100 frames)
                break;
            case YELLOW:
                state = RED;
                timer = 165;  // 5 segundos para rojo (165 frames)
                break;
            case RED:
                state = GREEN;
                timer = 100;  // 3 segundos para verde (100 frames)
                break;
        }
    }
    // Advertencia cuando el verde está por terminar
    else if(state == GREEN && timer < 50) {  // Parpadeo en últimos 1.5 segundos
        if(timer % 10 < 5) {  // Parpadeo más rápido
            state = GREEN;
        }
    }
}

void TrafficLight::draw() const {
    // Dibujar caja del semáforo
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    
    if (direction == 0) { // Vertical
        bar(x - 10, y - 30, x + 10, y + 30);
    } else { // Horizontal
        bar(x - 30, y - 10, x + 30, y + 10);
    }
    
    // Dibujar luz según el estado
    if (state == RED) {
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
    } else if (state == YELLOW) {
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
    } else {
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
    }
    
    // Dibujar el círculo del semáforo
    fillellipse(x, y, 8, 8);
}