#include <stdlib.h>
#include <graphics.h>
#include "Obstacle.h"

// Definición de constantes de color
#define RED 4
#define BLUE 1
#define CYAN 3
#define MAGENTA 5
#define BROWN 6
#define BLACK 0

// Constructor
Obstacle::Obstacle(int startX, int startY, int dx, int dy, int obstacleType) {
    x = startX;
    y = startY;
    this->dx = dx;
    this->dy = dy;
    
    // Colores según tipo de obstáculo
    if (obstacleType == 0) { // Carro
        color = BLUE;
    } else if (obstacleType == 1) { // Camión
        color = BROWN;
    } else { // Barricada
        color = RED;
    }
    
    this->type = obstacleType;
    
    // Establecer dimensiones según el tipo
    if (type == 0) { // Carro
        width = 20;
        height = 30;
    } else if (type == 1) { // Camión
        width = 25;
        height = 40;
    } else { // Barricada
        width = 15;
        height = 15;
    }
    
    next = nullptr;
}

// Destructor
Obstacle::~Obstacle() {
    // No necesita realizar acciones específicas
}

// Getters
int Obstacle::getX() const {
    return x;
}

int Obstacle::getY() const {
    return y;
}

int Obstacle::getDX() const {
    return dx;
}

int Obstacle::getDY() const {
    return dy;
}

int Obstacle::getColor() const {
    return color;
}

int Obstacle::getType() const {
    return type;
}

int Obstacle::getWidth() const {
    return width;
}

int Obstacle::getHeight() const {
    return height;
}

Obstacle* Obstacle::getNext() const {
    return next;
}

// Setters
void Obstacle::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Obstacle::setDirection(int dx, int dy) {
    this->dx = dx;
    this->dy = dy;
}

void Obstacle::setColor(int color) {
    this->color = color;
}

void Obstacle::setType(int type) {
    this->type = type;
}

void Obstacle::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

void Obstacle::setNext(Obstacle* next) {
    this->next = next;
}

// Comportamiento
void Obstacle::move() {
    // Mover el obstáculo
    x += dx * 2; // Velocidad más lenta que el jugador
    y += dy * 2;
    
    // Cambiar dirección si llega a una intersección (aleatorio)
    if ((x >= 140 && x <= 160 && (y == 150 || y == 250 || y == 350)) ||
        (y >= 140 && y <= 160 && (x == 150 || x == 250 || x == 350)) ||
        (x >= 240 && x <= 260 && (y == 150 || y == 250 || y == 350)) ||
        (y >= 240 && y <= 260 && (x == 150 || x == 250 || x == 350)) ||
        (x >= 340 && x <= 360 && (y == 150 || y == 250 || y == 350)) ||
        (y >= 340 && y <= 360 && (x == 150 || x == 250 || x == 350))) {
        
        if (rand() % 100 < 20) { // 20% de probabilidad de cambiar dirección
            changeDirection();
        }
    }
    
    // Si el obstáculo se sale de la pantalla, reubicarlo
    if (x < -50 || x > 650 || y < -50 || y > 650) {
        // Determinar punto de entrada aleatorio
        int side = rand() % 4; // 0: arriba, 1: derecha, 2: abajo, 3: izquierda
        
        switch (side) {
            case 0: // Arriba
                x = 150 + (rand() % 3) * 100;
                y = -30;
                dx = 0;
                dy = 1;
                break;
            case 1: // Derecha
                x = 650;
                y = 150 + (rand() % 3) * 100;
                dx = -1;
                dy = 0;
                break;
            case 2: // Abajo
                x = 150 + (rand() % 3) * 100;
                y = 510;
                dx = 0;
                dy = -1;
                break;
            case 3: // Izquierda
                x = -30;
                y = 150 + (rand() % 3) * 100;
                dx = 1;
                dy = 0;
                break;
        }
    }
}

void Obstacle::draw() const {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    
    // Ajustar la posición según la dirección
    if (dx != 0) {
        // Obstáculo horizontal
        bar(x - width/2, y - height/2, x + width/2, y + height/2);
        
        // Detalles del obstáculo
        setcolor(BLACK);
        if (type == 0) { // Carro
            rectangle(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x - width/4, y - height/2, x - width/4, y + height/2);
            line(x + width/4, y - height/2, x + width/4, y + height/2);
        } else if (type == 1) { // Camión
            rectangle(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x, y - height/2, x, y + height/2);
        } else { // Barricada
            rectangle(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x - width/2, y + height/2, x + width/2, y - height/2);
        }
    } else {
        // Obstáculo vertical
        bar(x - height/2, y - width/2, x + height/2, y + width/2);
        
        // Detalles del obstáculo
        setcolor(BLACK);
        if (type == 0) { // Carro
            rectangle(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y - width/4, x + height/2, y - width/4);
            line(x - height/2, y + width/4, x + height/2, y + width/4);
        } else if (type == 1) { // Camión
            rectangle(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y, x + height/2, y);
        } else { // Barricada
            rectangle(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y + width/2, x + height/2, y - width/2);
        }
    }
}

bool Obstacle::checkCollision(int playerX, int playerY, int playerWidth, int playerHeight) const {
    int obstacleLeft, obstacleRight, obstacleTop, obstacleBottom;
    int playerLeft, playerRight, playerTop, playerBottom;
    
    // Ajustar según la orientación del obstáculo
    if (dx != 0) {
        obstacleLeft = x - width/2;
        obstacleRight = x + width/2;
        obstacleTop = y - height/2;
        obstacleBottom = y + height/2;
    } else {
        obstacleLeft = x - height/2;
        obstacleRight = x + height/2;
        obstacleTop = y - width/2;
        obstacleBottom = y + width/2;
    }
    
    // Ajustar según la orientación del jugador (asumiendo que es vertical u horizontal)
    if (playerWidth > playerHeight) {
        playerLeft = playerX - playerWidth/2;
        playerRight = playerX + playerWidth/2;
        playerTop = playerY - playerHeight/2;
        playerBottom = playerY + playerHeight/2;
    } else {
        playerLeft = playerX - playerHeight/2;
        playerRight = playerX + playerHeight/2;
        playerTop = playerY - playerWidth/2;
        playerBottom = playerY + playerWidth/2;
    }
    
    // Verificar si hay colisión
    return (obstacleLeft < playerRight && 
            obstacleRight > playerLeft && 
            obstacleTop < playerBottom && 
            obstacleBottom > playerTop);
}

void Obstacle::changeDirection() {
    // Cambiar dirección aleatoriamente
    int newDirection = rand() % 4;
    
    switch (newDirection) {
        case 0: // Norte
            dx = 0;
            dy = -1;
            break;
        case 1: // Este
            dx = 1;
            dy = 0;
            break;
        case 2: // Sur
            dx = 0;
            dy = 1;
            break;
        case 3: // Oeste
            dx = -1;
            dy = 0;
            break;
    }
}

// Funciones para gestionar la lista
void addObstacle(Obstacle** head, Obstacle* newObstacle) {
    if (head == nullptr || newObstacle == nullptr) return;
    
    if (*head == nullptr) {
        *head = newObstacle;
        return;
    }
    
    Obstacle* current = *head;
    while (current->getNext() != nullptr) {
        current = current->getNext();
    }
    
    current->setNext(newObstacle);
}

void removeObstacle(Obstacle** head, Obstacle* obstacle) {
    if (head == nullptr || *head == nullptr || obstacle == nullptr) return;
    
    // Si el obstáculo a eliminar es el primero
    if (*head == obstacle) {
        *head = (*head)->getNext();
        return;
    }
    
    // Buscar el obstáculo
    Obstacle* current = *head;
    while (current != nullptr && current->getNext() != obstacle) {
        current = current->getNext();
    }
    
    // Si se encontró, ajustar los punteros
    if (current != nullptr) {
        current->setNext(obstacle->getNext());
    }
}