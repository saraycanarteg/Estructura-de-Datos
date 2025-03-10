#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

#include "Vehicle.h"
#include "TrafficLight.h"
#include "Crossroad.h"
#include "RecordManager.h"

class Simulation
{
private:
    std::string playerName;
    int survivalTime;
    RecordManager recordManager;

    // Lista de vehículos
    Vehicle *vehicles;

    // Semáforos
    TrafficLight *trafficLights[18];

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

    void setPlayerName(const std::string& name);
    
    std::string getPlayerName() const;

    void saveRecord();
    int calculateScore();
    void displayRecords();

    // Limpieza de recursos
    void cleanup();
};

#endif