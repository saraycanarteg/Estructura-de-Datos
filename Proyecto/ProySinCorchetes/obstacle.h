#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
private:
    int x, y;               // Posición
    int dx, dy;             // Dirección y velocidad
    int color;              // Color
    int width, height;      // Dimensiones
    int type;               // Tipo de obstáculo (0=carro, 1=camión, 2=barricada)
    Obstacle* next;         // Puntero al siguiente obstáculo

public:
    // Constructor y destructor
    Obstacle(int startX, int startY, int dx, int dy, int obstacleType);
    ~Obstacle();

    // Getters
    int getX() const;
    int getY() const;
    int getDX() const;
    int getDY() const;
    int getColor() const;
    int getType() const;
    int getWidth() const;
    int getHeight() const;
    Obstacle* getNext() const;

    // Setters
    void setPosition(int x, int y);
    void setDirection(int dx, int dy);
    void setColor(int color);
    void setType(int type);
    void setDimensions(int width, int height);
    void setNext(Obstacle* next);

    // Funciones de comportamiento
    void move();
    void draw() const;
    bool checkCollision(int playerX, int playerY, int playerWidth, int playerHeight) const;
    void changeDirection();
};

// Funciones para gestionar la lista de obstáculos
void addObstacle(Obstacle** head, Obstacle* newObstacle);
void removeObstacle(Obstacle** head, Obstacle* obstacle);

#endif