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
}

// Destructor
Simulation::~Simulation() {
    cleanup();
}

// Inicializar la simulación
void Simulation::initialize() {
    int gd = DETECT, gm;
    
    // Inicializar gráficos
    initgraph(&gd, &gm, (char*)"");
    
    // Inicializar generador de números aleatorios
    srand(time(NULL));
    
    // Crear semáforos para las cuatro direcciones
    trafficLights[0] = new TrafficLight(250, 150, 0); // Norte
    trafficLights[1] = new TrafficLight(450, 250, 1); // Este
    trafficLights[2] = new TrafficLight(250, 350, 0); // Sur
    trafficLights[3] = new TrafficLight(150, 250, 1); // Oeste
    
    // Establecer estados iniciales de los semáforos
    trafficLights[0]->setState(GREEN);
    trafficLights[2]->setState(GREEN);
    trafficLights[1]->setState(RED);
    trafficLights[3]->setState(RED);
    
    // Temporizadores
    trafficLights[0]->setTimer(100);
    trafficLights[1]->setTimer(100);
    trafficLights[2]->setTimer(100);
    trafficLights[3]->setTimer(100);
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

// Ejecutar la simulación
void Simulation::run() {
    char key;
    
    // Bucle principal
    while (running) {
        cleardevice();
        
        // Dibujar el cruce
        crossroad.draw();
        
        // Actualizar y dibujar semáforos
        for (int i = 0; i < 4; i++) {
            trafficLights[i]->update();
            trafficLights[i]->draw();
        }
        
        // Generar vehículos aleatoriamente
        generateRandomVehicle();
        
        // Actualizar y dibujar vehículos
        updateVehicles();
        
        // Mostrar información
        setcolor(WHITE);
        outtextxy(10, 10, (char*)"Simulación de Cruce de Caminos");
        outtextxy(10, 30, (char*)"Presiona ESC para salir");
        
        // Detectar tecla ESC para salir
        if (kbhit()) {
            key = getch();
            if (key == 27) { // ESC
                running = 0;
            }
        }
        
        delay(30);
        frameCount++;
    }
}

// Limpiar recursos
void Simulation::cleanup() {
    // Liberar memoria de los vehículos
    cleanupVehicles();
    
    // Liberar memoria de los semáforos
    for (int i = 0; i < 4; i++) {
        delete trafficLights[i];
        trafficLights[i] = nullptr;
    }
    
    // Cerrar el modo gráfico
    closegraph();
}