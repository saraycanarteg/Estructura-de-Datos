#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

class TrafficLight {
private:
    int x, y;             // Posición
    int state;            // Estado (rojo, amarillo, verde)
    int timer;            // Temporizador
    int direction;        // Dirección (0=vertical, 1=horizontal)

public:
    // Constructor y destructor
    TrafficLight(int x, int y, int direction);
    ~TrafficLight();

    // Getters
    int getX() const;
    int getY() const;
    int getState() const;
    int getDirection() const;

    // Setters
    void setState(int state);
    void setTimer(int timer);

    // Comportamiento
    void update();
    void draw() const;
};

#endif