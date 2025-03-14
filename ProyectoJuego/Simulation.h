#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

#include "Vehicle.h"
#include "TrafficLight.h"
#include "Crossroad.h"
#include "RecordManager.h"
#include "Obstacle.h"
#include "Navigator.h"

class Simulation
{
private:
    std::string playerName;
    int survivalTime;
    RecordManager recordManager;

    // Lista de vehículos y obstaculos
    Vehicle *vehicles;
    Obstacle *obstacles;

    // Semáforos
    TrafficLight *trafficLights[18];

    // Cruce
    Crossroad crossroad;
    Navigator navigator;

    // Variables de misión
    bool missionCompleted ;
    bool hasMission;
    int score;
    int destinationX;
    int destinationY;

    // Variables de control
    int running;
    int frameCount;
    int obstacleSpawnTimer;

    // Funciones auxiliares
    void generateRandomVehicle();
    void updateVehicles();
    void cleanupVehicles();
    void generateRandomObstacle();
    void updateObstacles();
    void cleanupObstacles();
    void checkCollisions();
    bool checkObstacleCollisions();
    void setRandomDestination();
    void completeMission();
    void updateNavigation();
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