#ifndef SIMULATION_H
#define SIMULATION_H


#include "Vehicle.cpp"
#include "TrafficLight.cpp"
#include "Crossroad.cpp"

class Simulation {
private:
    // Lista de vehículos
    Vehicle* vehicles;
    
    // Semáforos
    TrafficLight* trafficLights[4];
    
    // Cruce
    Crossroad crossroad;
    
    // Variables de control
    int running;
    int frameCount;
    
    // Funciones auxiliares
    void generateRandomVehicle();
    void updateVehicles();
    void cleanupVehicles();

public:
    // Constructor y destructor
    Simulation();
    ~Simulation();
    
    // Inicializar y ejecutar la simulación
    void initialize();
    void run();
    
    // Limpieza de recursos
    void cleanup();
};

#endif