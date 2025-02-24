#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Dimensiones de la ventana
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

VehicleNode createVehicle() {
    float* vehicle = malloc(sizeof(float) * 7);
    // x, y, angle, speed, max_speed, width, height
    vehicle[0] = SCREEN_WIDTH / 2;  // x
    vehicle[1] = SCREEN_HEIGHT / 2; // y
    vehicle[2] = 0.0f;              // angle
    vehicle[3] = 0.0f;              // speed
    vehicle[4] = 5.0f;              // max_speed
    vehicle[5] = 30.0f;             // width
    vehicle[6] = 50.0f;             // height
    return vehicle;
}

// Acceder a las propiedades del vehículo
float getVehicleX(VehicleNode vehicle) {
    float* v = (float*)vehicle;
    return v[0];
}

void setVehicleX(VehicleNode vehicle, float x) {
    float* v = (float*)vehicle;
    v[0] = x;
}

float getVehicleY(VehicleNode vehicle) {
    float* v = (float*)vehicle;
    return v[1];
}

void setVehicleY(VehicleNode vehicle, float y) {
    float* v = (float*)vehicle;
    v[1] = y;
}

float getVehicleAngle(VehicleNode vehicle) {
    float* v = (float*)vehicle;
    return v[2];
}

void setVehicleAngle(VehicleNode vehicle, float angle) {
    float* v = (float*)vehicle;
    v[2] = angle;
}

float getVehicleSpeed(VehicleNode vehicle) {
    float* v = (float*)vehicle;
    return v[3];
}

void setVehicleSpeed(VehicleNode vehicle, float speed) {
    float* v = (float*)vehicle;
    v[3] = speed;
}

float getVehicleMaxSpeed(VehicleNode vehicle) {
    float* v = (float*)vehicle;
    return v[4];
}

float getVehicleWidth(VehicleNode vehicle) {
    float* v = (float*)vehicle;
    return v[5];
}

float getVehicleHeight(VehicleNode vehicle) {
    float* v = (float*)vehicle;
    return v[6];
}