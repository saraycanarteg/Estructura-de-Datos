#include <graphics.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Simulation.h"
#include "RecordManager.h"

// Definición de constantes de color
#define RED 4
#define GREEN 2
#define YELLOW 14
#define WHITE 15

// Constructor
Simulation::Simulation() {
    vehicles = nullptr;
    obstacles = nullptr;
    trafficLightsList = nullptr;
    running = 1;
    frameCount = 0;
    survivalTime = 0;
    score = 0;
    missionCompleted = false;
    hasMission = false;
    vehicles = new Vehicle(20, 150, 1, 0, 0);
}

void Simulation::addTrafficLight(TrafficLight* light) {
    TrafficLightNode* newNode = new TrafficLightNode(light);
    if (!trafficLightsList) {
        trafficLightsList = newNode;
    } else {
        newNode->next = trafficLightsList;
        trafficLightsList = newNode;
    }
}

// Destructor
Simulation::~Simulation()
{
    cleanup();
}

// Inicializar la simulación
void Simulation::initialize() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    srand(time(NULL));
    setbkcolor(GREEN);
    cleardevice();

    // Crear semáforos como lista enlazada
    addTrafficLight(new TrafficLight(150, 150, 0));
    addTrafficLight(new TrafficLight(150, 150, 1));
    addTrafficLight(new TrafficLight(250, 150, 0));
    addTrafficLight(new TrafficLight(250, 150, 1));
    addTrafficLight(new TrafficLight(350, 150, 0));
    addTrafficLight(new TrafficLight(350, 150, 1));
    addTrafficLight(new TrafficLight(150, 250, 0));
    addTrafficLight(new TrafficLight(150, 250, 1));
    addTrafficLight(new TrafficLight(250, 250, 0));
    addTrafficLight(new TrafficLight(250, 250, 1));
    addTrafficLight(new TrafficLight(350, 250, 0));
    addTrafficLight(new TrafficLight(350, 250, 1));
    addTrafficLight(new TrafficLight(150, 350, 0));
    addTrafficLight(new TrafficLight(150, 350, 1));
    addTrafficLight(new TrafficLight(250, 350, 0));
    addTrafficLight(new TrafficLight(250, 350, 1));
    addTrafficLight(new TrafficLight(350, 350, 0));
    addTrafficLight(new TrafficLight(350, 350, 1));

    // Inicializar estados de semáforos
    int count = 0;
    TrafficLightNode* current = trafficLightsList;
    while (current != nullptr) {
        if (count % 2 == 0) {
            current->light->setState(GREEN);
        } else {
            current->light->setState(RED);
        }
        current->light->setTimer(100);
        count++;
        current = current->next;
    }
}

void Simulation::generateRandomObstacle()
{
    if (frameCount % 120 == 0)
    { // Generate obstacle every 4 seconds (30 frames/sec)
        int direction = rand() % 4;
        int obstacleType = rand() % 3; // 0=small, 1=medium, 2=large

        Obstacle *newObstacle = nullptr;

        switch (direction)
        {
        case 0: // North to South
            newObstacle = new Obstacle(150 + (rand() % 3) * 100, 0, 0, 1, obstacleType);
            break;
        case 1: // East to West
            newObstacle = new Obstacle(640, 150 + (rand() % 3) * 100, -1, 0, obstacleType);
            break;
        case 2: // South to North
            newObstacle = new Obstacle(150 + (rand() % 3) * 100, 480, 0, -1, obstacleType);
            break;
        case 3: // West to East
            newObstacle = new Obstacle(0, 150 + (rand() % 3) * 100, 1, 0, obstacleType);
            break;
        }

        if (newObstacle != nullptr)
        {
            addObstacle(&obstacles, newObstacle);
        }
    }
}
void Simulation::updateObstacles()
{
    Obstacle *current = obstacles;

    while (current != nullptr)
    {
        Obstacle *next = current->getNext();

        current->move();
        current->draw();

        // Check if obstacle is off-screen
        int x = current->getX();
        int y = current->getY();

        if (x < -50 || x > 650 || y < -50 || y > 650)
        {
            removeObstacle(&obstacles, current);
            delete current;
        }

        current = next;
    }
}

// Cleanup obstacles
void Simulation::cleanupObstacles()
{
    Obstacle *current = obstacles;

    while (current != nullptr)
    {
        Obstacle *next = current->getNext();
        delete current;
        current = next;
    }

    obstacles = nullptr;
}
void Simulation::updateNavigation()
{
    if (!hasMission)
        return;

    // Draw the minimap
    navigator.drawMinimap();

    // Check if destination reached
    if (navigator.hasReachedDestination(vehicles->getX(), vehicles->getY()))
    {
        setcolor(GREEN);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(150, 200, (char *)"MISSION COMPLETED!");

        score += 1000; // Bonus points for completing mission
        missionCompleted = true;

        // Set a new destination after a delay
        if (frameCount % 150 == 0 && missionCompleted)
        {
            navigator.setDestination(rand() % 640, rand() % 480);
            missionCompleted = false;
        }
    }
}
// Check for collisions between player and obstacles
void Simulation::checkCollisions()
{
    if (vehicles == nullptr)
        return;

    Obstacle *current = obstacles;

    while (current != nullptr)
    {
        if (current->checkCollision(vehicles->getX(), vehicles->getY(),
                                    vehicles->getWidth(), vehicles->getHeight()))
        {
            setcolor(RED);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(150, 250, (char *)"COLLISION! GAME OVER");

            delay(3000);
            running = 0;
            break;
        }

        current = current->getNext();
    }
}

// Generar vehículo aleatorio
void Simulation::generateRandomVehicle()
{
    if (frameCount % 30 == 0)
    {
        int direction = rand() % 4;
        int vehicleType = rand() % 2;

        Vehicle *newVehicle = nullptr;

        switch (direction)
        {
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

        if (newVehicle != nullptr)
        {
            addVehicle(&vehicles, newVehicle);
        }
    }
}

// Actualizar los vehículos
void Simulation::updateVehicles()
{
    Vehicle *current = vehicles;

    while (current != nullptr)
    {
        Vehicle *next = current->getNext();

        current->move();
        current->draw();

        // Verificar si el vehículo está fuera de la pantalla
        int x = current->getX();
        int y = current->getY();

        if (x < -50 || x > 650 || y < -50 || y > 650)
        {
            removeVehicle(&vehicles, current);
            delete current;
        }

        current = next;
    }
}

// Limpiar vehículos
void Simulation::cleanupVehicles()
{
    Vehicle *current = vehicles;

    while (current != nullptr)
    {
        Vehicle *next = current->getNext();
        delete current;
        current = next;
    }

    vehicles = nullptr;
}

void Simulation::run()
{
    char key;
    bool paused = false;
    survivalTime = 0; // Initialize survival time
    score = 0;
    missionCompleted = false;
    bool redLightViolation = false;
    bool returnToMenu = false;

    while (running)
    {
        cleardevice();
        crossroad.draw();

        // Actualizar y dibujar semáforos usando la lista enlazada
        TrafficLightNode* current = trafficLightsList;
        bool redLightViolation = false;

        while (current != nullptr) 
        {
            current->light->update();
            current->light->draw();

            // Verificar violación solo si el vehículo existe
            if (vehicles != nullptr)
            {
                int playerX = vehicles->getX();
                int playerY = vehicles->getY();

                if (abs(current->light->getX() - playerX) < 50 &&
                    abs(current->light->getY() - playerY) < 50 &&
                    current->light->getState() == RED)
                {
                    redLightViolation = true;
                    break;
                }
            }
            current = current->next;
        }

        generateRandomObstacle();
        updateObstacles();
        checkCollisions();
        updateNavigation();

        // Check for red light violation
        if (vehicles != nullptr && !redLightViolation)
        {
            int vehicleX = vehicles->getX();
            int vehicleY = vehicles->getY();

            // Check through all traffic lights using lista enlazada
            current = trafficLightsList;
            while (current != nullptr)
            {
                if (abs(current->light->getX() - vehicleX) < 50 &&
                    abs(current->light->getY() - vehicleY) < 50 &&
                    current->light->getState() == RED)
                {
                    redLightViolation = true;
                    break;
                }
                current = current->next;
            }
        }

        if (redLightViolation)
        {
            setcolor(RED);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(150, 250, (char *)"GAME OVER");

            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            char scoreText[100];
            sprintf(scoreText, "Puntuacion: %d", calculateScore());
            outtextxy(150, 300, scoreText);

            saveRecord(); // Save the record

            delay(3000);
            running = 0;
            break;
        }

        if (kbhit())
        {
            key = getch();
            if (key == 27)
            { // ESC
                running = 0;
            }
            else if (key == 32)
            { // Space bar
                paused = !paused;
            }
            else if (!paused && vehicles != nullptr)
            {
                if (key == 72)
                { // Up arrow
                    vehicles->setDirection(0, -1);
                }
                else if (key == 80)
                { // Down arrow
                    vehicles->setDirection(0, 1);
                }
                else if (key == 75)
                { // Left arrow
                    vehicles->setDirection(-1, 0);
                }
                else if (key == 77)
                { // Right arrow
                    vehicles->setDirection(1, 0);
                }
            }
        }

        // Mover el vehículo solo si no está pausado
        if (!paused && vehicles != nullptr)
        {
            vehicles->move();
        }

        // Dibujar el vehículo siempre, esté pausado o no
        if (vehicles != nullptr)
        {
            vehicles->draw();

            // Verificar si está fuera de la carretera
            if (!vehicles->isOnRoad())
            {
                setcolor(RED);
                outtextxy(200, 200, (char *)"GAME OVER! Te saliste de la carretera");
                delay(2000);
                running = 0;
            }
        }

        setcolor(WHITE);
        outtextxy(10, 10, (char *)"Use las flechas para mover");
        outtextxy(10, 30, (char *)"Espacio para frenar");
        outtextxy(10, 50, (char *)"ESC para salir");
        char scoreText[50];
        sprintf(scoreText, "Score: %d", score + (survivalTime / 30) * 10);
        outtextxy(10, 70, scoreText);

        if (!paused)
        {
            survivalTime++;
            score = (survivalTime / 30) * 10;
        }

        delay(30);
        frameCount++;
    }
}

// Limpiar recursos
void Simulation::cleanup() {
    // Limpiar semáforos
    while (trafficLightsList != nullptr) {
        TrafficLightNode* temp = trafficLightsList;
        trafficLightsList = trafficLightsList->next;
        delete temp->light;
        delete temp;
    }

    cleanupVehicles();
    cleanupObstacles();
    closegraph();
}

void Simulation::setPlayerName(const std::string &name)
{
    playerName = name;
}

std::string Simulation::getPlayerName() const
{
    return playerName;
}

void Simulation::saveRecord()
{
    recordManager.loadRecords();
    recordManager.addRecord(playerName, calculateScore());
    recordManager.saveRecords();
}

int Simulation::calculateScore()
{
    return (survivalTime / 30) * 100; // Assuming 30 frames per second
}

void Simulation::displayRecords()
{
    recordManager.loadRecords();
    recordManager.displayRecords(150, 100);
}