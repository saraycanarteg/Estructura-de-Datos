#include <stdlib.h>
#include <graphics.h>
#include "Vehicle.h"


// Definición de constantes de color
#define RED 4
#define BLUE 1
#define GREEN 2
#define YELLOW 14
#define WHITE 15
#define BLACK 0

// Constructor
Vehicle::Vehicle(int startX, int startY, int dx, int dy, int vehicleType) {
    x = startX;
    y = startY;
    this->dx = dx;
    this->dy = dy;
    
    // Color aleatorio para el vehículo
    int colors[] = {RED, BLUE, GREEN, YELLOW, WHITE};
    color = colors[rand() % 5];
    
    this->vehicleType = vehicleType;
    
    // Establecer dimensiones según el tipo
    if (vehicleType == 0) { // Carro
        width = 20;
        height = 30;
    } else { // Camión
        width = 25;
        height = 40;
    }
    
    next = nullptr;
}

// Destructor
Vehicle::~Vehicle() {
    // No necesita realizar acciones específicas
}

// Getters
int Vehicle::getX() const {
    return x;
}

int Vehicle::getY() const {
    return y;
}

int Vehicle::getDX() const {
    return dx;
}

int Vehicle::getDY() const {
    return dy;
}

int Vehicle::getColor() const {
    return color;
}

int Vehicle::getType() const {
    return vehicleType;
}

int Vehicle::getWidth() const {
    return width;
}

int Vehicle::getHeight() const {
    return height;
}

Vehicle* Vehicle::getNext() const {
    return next;
}

// Setters
void Vehicle::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Vehicle::setDirection(int dx, int dy) {
    this->dx = dx;
    this->dy = dy;
}

void Vehicle::setColor(int color) {
    this->color = color;
}

void Vehicle::setType(int type) {
    this->vehicleType = type;
}

void Vehicle::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

void Vehicle::setNext(Vehicle* next) {
    this->next = next;
}

// Comportamiento
void Vehicle::move() {
    // Mover el vehículo
    x += dx * 3;
    y += dy * 3;
}

void Vehicle::draw() const {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    
    // Ajustar la posición según la dirección
    if (dx != 0) {
        // Vehículo horizontal
        bar(x - width/2, y - height/2, x + width/2, y + height/2);
        
        // Detalles del vehículo
        setcolor(BLACK);
        if (vehicleType == 0) { // Carro
            rectangle(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x - width/4, y - height/2, x - width/4, y + height/2);
            line(x + width/4, y - height/2, x + width/4, y + height/2);
        } else { // Camión
            rectangle(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x, y - height/2, x, y + height/2);
        }
    } else {
        // Vehículo vertical
        bar(x - height/2, y - width/2, x + height/2, y + width/2);
        
        // Detalles del vehículo
        setcolor(BLACK);
        if (vehicleType == 0) { // Carro
            rectangle(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y - width/4, x + height/2, y - width/4);
            line(x - height/2, y + width/4, x + height/2, y + width/4);
        } else { // Camión
            rectangle(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y, x + height/2, y);
        }
    }
}

// Funciones para gestionar la lista
void addVehicle(Vehicle** head, Vehicle* newVehicle) {
    if (head == nullptr || newVehicle == nullptr) return;
    
    if (*head == nullptr) {
        *head = newVehicle;
        return;
    }
    
    Vehicle* current = *head;
    while (current->getNext() != nullptr) {
        current = current->getNext();
    }
    
    current->setNext(newVehicle);
}

void removeVehicle(Vehicle** head, Vehicle* vehicle) {
    if (head == nullptr || *head == nullptr || vehicle == nullptr) return;
    
    // Si el vehículo a eliminar es el primero
    if (*head == vehicle) {
        *head = (*head)->getNext();
        return;
    }
    
    // Buscar el vehículo
    Vehicle* current = *head;
    while (current != nullptr && current->getNext() != vehicle) {
        current = current->getNext();
    }
    
    // Si se encontró, ajustar los punteros
    if (current != nullptr) {
        current->setNext(vehicle->getNext());
    }
}
// Add to Vehicle.cpp
bool Vehicle::isOnRoad() const {
    // Check if vehicle is on any horizontal road
    bool onHorizontalRoad = (y >= 120 && y <= 180) || 
                           (y >= 220 && y <= 280) || 
                           (y >= 320 && y <= 380);
    
    // Check if vehicle is on any vertical road
    bool onVerticalRoad = (x >= 120 && x <= 180) || 
                         (x >= 220 && x <= 280) || 
                         (x >= 320 && x <= 380);
    
    return onHorizontalRoad || onVerticalRoad;
}

void Vehicle::handleInput(char key) {
    switch(key) {
        case 72: // Up arrow
            dy = -1;
            dx = 0;
            break;
        case 80: // Down arrow
            dy = 1;
            dx = 0;
            break;
        case 75: // Left arrow
            dx = -1;
            dy = 0;
            break;
        case 77: // Right arrow
            dx = 1;
            dy = 0;
            break;
    }
}