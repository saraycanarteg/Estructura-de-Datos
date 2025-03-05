#include <graphics.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Simulation.h"

// Definición de constantes de color
#define RED 4
#define GREEN 2
#define YELLOW 14
#define WHITE 15

// Constructor
Simulation::Simulation() {
    vehicles = nullptr;
    running = 1;
    frameCount = 0;
    vehicles = new Vehicle(0, 250, 1, 0, 0); 
}

// Destructor
Simulation::~Simulation() {
    cleanup();
}

// Inicializar la simulación
// En Simulation::initialize()
void Simulation::initialize() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    srand(time(NULL));

    setbkcolor(GREEN);
    cleardevice(); // Limpiar la pantalla para aplicar el nuevo color
    
    srand(time(NULL));
    
    // Crear semáforos para cada intersección (9 intersecciones, 4 semáforos cada una)
    // Intersección Superior Izquierda
    trafficLights[0] = new TrafficLight(150, 150, 0);
    trafficLights[1] = new TrafficLight(150, 150, 1);
    
    // Intersección Superior Central
    trafficLights[2] = new TrafficLight(250, 150, 0);
    trafficLights[3] = new TrafficLight(250, 150, 1);
    
    // Intersección Superior Derecha
    trafficLights[4] = new TrafficLight(350, 150, 0);
    trafficLights[5] = new TrafficLight(350, 150, 1);
    
    // Intersección Central Izquierda
    trafficLights[6] = new TrafficLight(150, 250, 0);
    trafficLights[7] = new TrafficLight(150, 250, 1);
    
    // Intersección Central
    trafficLights[8] = new TrafficLight(250, 250, 0);
    trafficLights[9] = new TrafficLight(250, 250, 1);
    
    // Intersección Central Derecha
    trafficLights[10] = new TrafficLight(350, 250, 0);
    trafficLights[11] = new TrafficLight(350, 250, 1);
    
    // Intersección Inferior Izquierda
    trafficLights[12] = new TrafficLight(150, 350, 0);
    trafficLights[13] = new TrafficLight(150, 350, 1);
    
    // Intersección Inferior Central
    trafficLights[14] = new TrafficLight(250, 350, 0);
    trafficLights[15] = new TrafficLight(250, 350, 1);
    
    // Intersección Inferior Derecha
    trafficLights[16] = new TrafficLight(350, 350, 0);
    trafficLights[17] = new TrafficLight(350, 350, 1);
    
    // Establecer estados iniciales alternados de los semáforos
    for(int i = 0; i < 18; i++) {
        if(i % 2 == 0) {
            trafficLights[i]->setState(GREEN);
        } else {
            trafficLights[i]->setState(RED);
        }
        trafficLights[i]->setTimer(100);
    }
}

// Generar vehículo aleatorio
void Simulation::generateRandomVehicle() {
    if (frameCount % 30 == 0) {
        int direction = rand() % 4;
        int vehicleType = rand() % 2;
        
        Vehicle* newVehicle = nullptr;
        
        switch (direction) {
            case 0: // Norte a Sur
                newVehicle = new Vehicle(250, 0, 0, 1, vehicleType);
                break;
            case 1: // Este a Oeste
                newVehicle = new Vehicle(600, 250, -1, 0, vehicleType);
                break;
            case 2: // Sur a Norte
                newVehicle = new Vehicle(350, 600, 0, -1, vehicleType);
                break;
            case 3: // Oeste a Este
                newVehicle = new Vehicle(0, 350, 1, 0, vehicleType);
                break;
        }
        
        if (newVehicle != nullptr) {
            addVehicle(&vehicles, newVehicle);
        }
    }
}

// Actualizar los vehículos
void Simulation::updateVehicles() {
    Vehicle* current = vehicles;
    
    while (current != nullptr) {
        Vehicle* next = current->getNext();
        
        current->move();
        current->draw();
        
        // Verificar si el vehículo está fuera de la pantalla
        int x = current->getX();
        int y = current->getY();
        
        if (x < -50 || x > 650 || y < -50 || y > 650) {
            removeVehicle(&vehicles, current);
            delete current;
        }
        
        current = next;
    }
}

// Limpiar vehículos
void Simulation::cleanupVehicles() {
    Vehicle* current = vehicles;
    
    while (current != nullptr) {
        Vehicle* next = current->getNext();
        delete current;
        current = next;
    }
    
    vehicles = nullptr;
}

void Simulation::run() {
    char key;
    bool paused = false;

    while (running) {
        cleardevice();
        
        // Dibujar el cruce
        crossroad.draw();
        
        // Actualizar y dibujar semáforos
        for (int i = 0; i < 18; i++) {
            trafficLights[i]->update();
            trafficLights[i]->draw();
        }

        if (kbhit()) {
            key = getch();
            if (key == 27) { // ESC
                running = 0;
            }
            else if (key == 32) { // Space bar
                paused = !paused;
            }
            else if (!paused && vehicles != nullptr) {
                if (key == 72) { // Up arrow
                    vehicles->setDirection(0, -1);
                }
                else if (key == 80) { // Down arrow
                    vehicles->setDirection(0, 1);
                }
                else if (key == 75) { // Left arrow
                    vehicles->setDirection(-1, 0);
                }
                else if (key == 77) { // Right arrow
                    vehicles->setDirection(1, 0);
                }
            }
        }
        
        // Mover el vehículo solo si no está pausado
        if (!paused && vehicles != nullptr) {
            vehicles->move();
        }
        
        // Dibujar el vehículo siempre, esté pausado o no
        if (vehicles != nullptr) {
            vehicles->draw();
            
            // Verificar si está fuera de la carretera
            if (!vehicles->isOnRoad()) {
                setcolor(RED);
                outtextxy(200, 200, (char*)"¡GAME OVER! Te saliste de la carretera");
                delay(2000);
                running = 0;
            }
        }

        setcolor(WHITE);
        outtextxy(10, 10, (char*)"Use las flechas para mover");
        outtextxy(10, 30, (char*)"Espacio para frenar");
        outtextxy(10, 50, (char*)"ESC para salir");
        
        delay(30);
        frameCount++;
    }
}

// Limpiar recursos
void Simulation::cleanup() {
    // Liberar memoria de los vehículos
    cleanupVehicles();
    
    // Liberar memoria de los semáforos
    for (int i = 0; i < 18; i++) {
        delete trafficLights[i];
        trafficLights[i] = nullptr;
    }

    // Cerrar el modo gráfico
    closegraph();
}

void Simulation::setPlayerName(const std::string& name) {
    playerName = name;
}

std::string Simulation::getPlayerName() const {
    return playerName;
}