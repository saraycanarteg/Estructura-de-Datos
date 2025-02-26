#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// Definición de constantes
#define RED 4
#define GREEN 2
#define YELLOW 14
#define BLUE 1
#define WHITE 15
#define BLACK 0

// Definición de nodos para representar vehículos sin usar struct
typedef void* VehicleNode;

// Funciones para crear y manipular nodos de vehículos
VehicleNode createVehicle(int startX, int startY, int dx, int dy, int vehicleType);
void setVehiclePosition(VehicleNode vehicle, int x, int y);
void setVehicleDirection(VehicleNode vehicle, int dx, int dy);
void setVehicleColor(VehicleNode vehicle, int color);
void setVehicleType(VehicleNode vehicle, int type);
void setVehicleDimensions(VehicleNode vehicle, int width, int height);
void setNextVehicle(VehicleNode vehicle, VehicleNode next);

int getVehicleX(VehicleNode vehicle);
int getVehicleY(VehicleNode vehicle);
int getVehicleDX(VehicleNode vehicle);
int getVehicleDY(VehicleNode vehicle);
int getVehicleColor(VehicleNode vehicle);
int getVehicleType(VehicleNode vehicle);
int getVehicleWidth(VehicleNode vehicle);
int getVehicleHeight(VehicleNode vehicle);
VehicleNode getNextVehicle(VehicleNode vehicle);

void moveVehicle(VehicleNode vehicle);
void drawVehicle(VehicleNode vehicle);
void freeVehicle(VehicleNode vehicle);
void addVehicle(VehicleNode* head, VehicleNode newVehicle);
void removeVehicle(VehicleNode* head, VehicleNode vehicle);

// Nodos para semáforos
typedef void* TrafficLightNode;

// Funciones para semáforos
TrafficLightNode createTrafficLight(int x, int y, int direction);
void setTrafficLightState(TrafficLightNode light, int state);
void setTrafficLightTimer(TrafficLightNode light, int timer);
int getTrafficLightX(TrafficLightNode light);
int getTrafficLightY(TrafficLightNode light);
int getTrafficLightState(TrafficLightNode light);
int getTrafficLightDirection(TrafficLightNode light);
void updateTrafficLight(TrafficLightNode light);
void drawTrafficLight(TrafficLightNode light);
void freeTrafficLight(TrafficLightNode light);

// Función para dibujar el cruce
void drawCrossroad();

// Implementación de la aplicación
int main() {
    int gd = DETECT, gm;
    int running = 1;
    char key;
    
    // Inicializar gráficos
    initgraph(&gd, &gm, (char*)"");
    
    // Inicializar generador de números aleatorios
    srand(time(NULL));
    
    // Crear lista de vehículos
    VehicleNode vehicles = NULL;
    VehicleNode current = NULL;
    
    // Crear semáforos para las cuatro direcciones
    TrafficLightNode trafficLights[4];
    trafficLights[0] = createTrafficLight(250, 150, 0); // Norte
    trafficLights[1] = createTrafficLight(450, 250, 1); // Este
    trafficLights[2] = createTrafficLight(250, 350, 0); // Sur
    trafficLights[3] = createTrafficLight(150, 250, 1); // Oeste
    
    // Establecer estados iniciales de los semáforos
    setTrafficLightState(trafficLights[0], GREEN);
    setTrafficLightState(trafficLights[2], GREEN);
    setTrafficLightState(trafficLights[1], RED);
    setTrafficLightState(trafficLights[3], RED);
    
    // Temporizadores
    setTrafficLightTimer(trafficLights[0], 100);
    setTrafficLightTimer(trafficLights[1], 100);
    setTrafficLightTimer(trafficLights[2], 100);
    setTrafficLightTimer(trafficLights[3], 100);
    
    int frameCount = 0;
    
    // Bucle principal
    while (running) {
        cleardevice();
        
        // Dibujar el cruce
        drawCrossroad();
        
        // Actualizar y dibujar semáforos
        for (int i = 0; i < 4; i++) {
            updateTrafficLight(trafficLights[i]);
            drawTrafficLight(trafficLights[i]);
        }
        
        // Generar vehículos aleatoriamente
        if (frameCount % 30 == 0) {
            int direction = rand() % 4;
            int vehicleType = rand() % 2;
            
            VehicleNode newVehicle = NULL;
            
            switch (direction) {
                case 0: // Norte a Sur
                    newVehicle = createVehicle(250, 0, 0, 1, vehicleType);
                    break;
                case 1: // Este a Oeste
                    newVehicle = createVehicle(600, 250, -1, 0, vehicleType);
                    break;
                case 2: // Sur a Norte
                    newVehicle = createVehicle(350, 600, 0, -1, vehicleType);
                    break;
                case 3: // Oeste a Este
                    newVehicle = createVehicle(0, 350, 1, 0, vehicleType);
                    break;
            }
            
            if (newVehicle != NULL) {
                addVehicle(&vehicles, newVehicle);
            }
        }
        
        // Actualizar y dibujar vehículos
   
        
        while (current != NULL) {
            VehicleNode next = getNextVehicle(current);
            
            moveVehicle(current);
            drawVehicle(current);
            
            // Eliminar vehículos fuera de la pantalla
            int x = getVehicleX(current);
            int y = getVehicleY(current);
            
            if (x < -50 || x > 650 || y < -50 || y > 650) {
                removeVehicle(&vehicles, current);
                freeVehicle(current);
            }
            
            current = next;
        }
        
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
    
  
    while (current != NULL) {
        VehicleNode next = getNextVehicle(current);
        freeVehicle(current);
        current = next;
    }
    
    for (int i = 0; i < 4; i++) {
        freeTrafficLight(trafficLights[i]);
    }
    
    closegraph();
    return 0;
}

// Implementación de las funciones de vehículos
VehicleNode createVehicle(int startX, int startY, int dx, int dy, int vehicleType) {
    // Asignamos memoria para los datos del vehículo (x, y, dx, dy, color, tipo, ancho, alto, siguiente)
    int* data = (int*)malloc(9 * sizeof(int));
    if (data == NULL) return NULL;
    
    data[0] = startX;      // x
    data[1] = startY;      // y
    data[2] = dx;          // dx
    data[3] = dy;          // dy
    
    // Color aleatorio para el vehículo
    int colors[] = {RED, BLUE, GREEN, YELLOW, WHITE};
    data[4] = colors[rand() % 5];  // color
    
    data[5] = vehicleType; // tipo
    
    // Establecer dimensiones según el tipo
    if (vehicleType == 0) { // Carro
        data[6] = 20;      // ancho
        data[7] = 30;      // alto
    } else { // Camión
        data[6] = 25;      // ancho
        data[7] = 40;      // alto
    }
    
    data[8] = 0;           // siguiente (NULL inicialmente)
    
    return (VehicleNode)data;
}

void setVehiclePosition(VehicleNode vehicle, int x, int y) {
    if (vehicle == NULL) return;
    int* data = (int*)vehicle;
    data[0] = x;
    data[1] = y;
}

void setVehicleDirection(VehicleNode vehicle, int dx, int dy) {
    if (vehicle == NULL) return;
    int* data = (int*)vehicle;
    data[2] = dx;
    data[3] = dy;
}

void setVehicleColor(VehicleNode vehicle, int color) {
    if (vehicle == NULL) return;
    int* data = (int*)vehicle;
    data[4] = color;
}

void setVehicleType(VehicleNode vehicle, int type) {
    if (vehicle == NULL) return;
    int* data = (int*)vehicle;
    data[5] = type;
}

void setVehicleDimensions(VehicleNode vehicle, int width, int height) {
    if (vehicle == NULL) return;
    int* data = (int*)vehicle;
    data[6] = width;
    data[7] = height;
}

void setNextVehicle(VehicleNode vehicle, VehicleNode next) {
    if (vehicle == NULL) return;
    int* data = (int*)vehicle;
    data[8] = (int)next;
}

int getVehicleX(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[0];
}

int getVehicleY(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[1];
}

int getVehicleDX(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[2];
}

int getVehicleDY(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[3];
}

int getVehicleColor(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[4];
}

int getVehicleType(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[5];
}

int getVehicleWidth(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[6];
}

int getVehicleHeight(VehicleNode vehicle) {
    if (vehicle == NULL) return 0;
    int* data = (int*)vehicle;
    return data[7];
}

VehicleNode getNextVehicle(VehicleNode vehicle) {
    if (vehicle == NULL) return NULL;
    int* data = (int*)vehicle;
    return (VehicleNode)data[8];
}

void moveVehicle(VehicleNode vehicle) {
    if (vehicle == NULL) return;
    
    int x = getVehicleX(vehicle);
    int y = getVehicleY(vehicle);
    int dx = getVehicleDX(vehicle);
    int dy = getVehicleDY(vehicle);
    
    // Verificar semáforos y ajustar velocidad
    // Este código se simplifica para el ejemplo
    
    // Mover el vehículo
    setVehiclePosition(vehicle, x + dx * 3, y + dy * 3);
}

void drawVehicle(VehicleNode vehicle) {
    if (vehicle == NULL) return;
    
    int x = getVehicleX(vehicle);
    int y = getVehicleY(vehicle);
    int width = getVehicleWidth(vehicle);
    int height = getVehicleHeight(vehicle);
    int color = getVehicleColor(vehicle);
    int type = getVehicleType(vehicle);
    
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    
    // Ajustar la posición según la dirección
    if (getVehicleDX(vehicle) != 0) {
        // Vehículo horizontal
        bar(x - width/2, y - height/2, x + width/2, y + height/2);
        
        // Detalles del vehículo
        setcolor(BLACK);
        if (type == 0) { // Carro
            rectangle(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x - width/4, y - height/2, x - width/4, y + height/2);
            line(x + width/4, y - height/2, x + width/4, y + height/2);
        } else { // Camión
            rectangle(x - width/2, y - height/2, x + width/2, y + height/2);
            line(x, y - height/2, x, y + height/2);
        }
    } else {
        // Vehículo vertical
        bar(x - height/2, y - width/2, x + height/2, y + width/2);
        
        // Detalles del vehículo
        setcolor(BLACK);
        if (type == 0) { // Carro
            rectangle(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y - width/4, x + height/2, y - width/4);
            line(x - height/2, y + width/4, x + height/2, y + width/4);
        } else { // Camión
            rectangle(x - height/2, y - width/2, x + height/2, y + width/2);
            line(x - height/2, y, x + height/2, y);
        }
    }
}

void freeVehicle(VehicleNode vehicle) {
    if (vehicle != NULL) {
        free(vehicle);
    }
}

void addVehicle(VehicleNode* head, VehicleNode newVehicle) {
    if (head == NULL || newVehicle == NULL) return;
    
    if (*head == NULL) {
        *head = newVehicle;
        return;
    }
    
    VehicleNode current = *head;
    while (getNextVehicle(current) != NULL) {
        current = getNextVehicle(current);
    }
    
    setNextVehicle(current, newVehicle);
}

void removeVehicle(VehicleNode* head, VehicleNode vehicle) {
    if (head == NULL || *head == NULL || vehicle == NULL) return;
    
    // Si el vehículo a eliminar es el primero
    if (*head == vehicle) {
        *head = getNextVehicle(*head);
        return;
    }
    
    // Buscar el vehículo
    VehicleNode current = *head;
    while (current != NULL && getNextVehicle(current) != vehicle) {
        current = getNextVehicle(current);
    }
    
    // Si se encontró, ajustar los punteros
    if (current != NULL) {
        setNextVehicle(current, getNextVehicle(vehicle));
    }
}

// Implementación de las funciones de semáforos
TrafficLightNode createTrafficLight(int x, int y, int direction) {
    // Formato de datos: x, y, estado, temporizador, dirección
    int* data = (int*)malloc(5 * sizeof(int));
    if (data == NULL) return NULL;
    
    data[0] = x;           // x
    data[1] = y;           // y
    data[2] = RED;         // estado inicial
    data[3] = 100;         // temporizador
    data[4] = direction;   // dirección
    
    return (TrafficLightNode)data;
}

void setTrafficLightState(TrafficLightNode light, int state) {
    if (light == NULL) return;
    int* data = (int*)light;
    data[2] = state;
}

void setTrafficLightTimer(TrafficLightNode light, int timer) {
    if (light == NULL) return;
    int* data = (int*)light;
    data[3] = timer;
}

int getTrafficLightX(TrafficLightNode light) {
    if (light == NULL) return 0;
    int* data = (int*)light;
    return data[0];
}

int getTrafficLightY(TrafficLightNode light) {
    if (light == NULL) return 0;
    int* data = (int*)light;
    return data[1];
}

int getTrafficLightState(TrafficLightNode light) {
    if (light == NULL) return 0;
    int* data = (int*)light;
    return data[2];
}

int getTrafficLightDirection(TrafficLightNode light) {
    if (light == NULL) return 0;
    int* data = (int*)light;
    return data[4];
}

void updateTrafficLight(TrafficLightNode light) {
    if (light == NULL) return;
    
    int* data = (int*)light;
    data[3]--; // Decrementar temporizador
    
    // Cambiar estado según el temporizador
    if (data[3] <= 0) {
        // Ciclo de semáforo: VERDE -> AMARILLO -> ROJO -> VERDE
        if (data[2] == GREEN) {
            data[2] = YELLOW;
            data[3] = 30; // Duración de amarillo
        } else if (data[2] == YELLOW) {
            data[2] = RED;
            data[3] = 100; // Duración de rojo
        } else {
            data[2] = GREEN;
            data[3] = 100; // Duración de verde
        }
    }
}

void drawTrafficLight(TrafficLightNode light) {
    if (light == NULL) return;
    
    int x = getTrafficLightX(light);
    int y = getTrafficLightY(light);
    int state = getTrafficLightState(light);
    int direction = getTrafficLightDirection(light);
    
    // Dibujar caja del semáforo
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    
    if (direction == 0) { // Vertical
        bar(x - 10, y - 30, x + 10, y + 30);
    } else { // Horizontal
        bar(x - 30, y - 10, x + 30, y + 10);
    }
    
    // Dibujar luz según el estado
    if (state == RED) {
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
    } else if (state == YELLOW) {
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
    } else {
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
    }
    
    if (direction == 0) { // Vertical
        fillellipse(x, y, 8, 8);
    } else { // Horizontal
        fillellipse(x, y, 8, 8);
    }
}

void freeTrafficLight(TrafficLightNode light) {
    if (light != NULL) {
        free(light);
    }
}

// Función para dibujar el cruce
void drawCrossroad() {
    // Fondo gris para las calles
    setcolor(8); // Gris oscuro
    setfillstyle(SOLID_FILL, 8);
    
    // Calle horizontal
    bar(0, 220, 640, 280);
    // Calle vertical
    bar(220, 0, 280, 480);
    
    // Líneas blancas de las calles
    setcolor(WHITE);
    setlinestyle(DASHED_LINE, 0, 1);
    
    // Líneas horizontales
    line(0, 250, 220, 250);
    line(280, 250, 640, 250);
    
    // Líneas verticales
    line(250, 0, 250, 220);
    line(250, 280, 250, 480);
    
    // Volver al estilo de línea normal
    setlinestyle(SOLID_LINE, 0, 1);
}