#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle {
private:
    int x, y;               // Posición
    int dx, dy;             // Dirección
    int color;              // Color
    int vehicleType;        // Tipo (0=carro, 1=camión)
    int width, height;      // Dimensiones
    Vehicle* next;          // Puntero al siguiente vehículo

public:
    // Constructor y destructor
    Vehicle(int startX, int startY, int dx, int dy, int vehicleType);
    ~Vehicle();

    // Funciones de acceso (getters)
    int getX() const;
    int getY() const;
    int getDX() const;
    int getDY() const;
    int getColor() const;
    int getType() const;
    int getWidth() const;
    int getHeight() const;
    Vehicle* getNext() const;

    // Funciones de modificación (setters)
    void setPosition(int x, int y);
    void setDirection(int dx, int dy);
    void setColor(int color);
    void setType(int type);
    void setDimensions(int width, int height);
    void setNext(Vehicle* next);

    // Funciones de comportamiento
    void move();
    void draw() const;
};

// Funciones para gestionar la lista de vehículos
void addVehicle(Vehicle** head, Vehicle* newVehicle);
void removeVehicle(Vehicle** head, Vehicle* vehicle);

#endif