#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

MapNode createMap() {
    void** map = malloc(sizeof(void*) * 2);
    map[0] = NULL;  // Lista de calles (head)
    map[1] = NULL;  // Destino
    return map;
}

// Acceder a propiedades del mapa
StreetNode getMapStreets(MapNode map) {
    void** m = (void**)map;
    return m[0];
}

void setMapStreets(MapNode map, StreetNode streets) {
    void** m = (void**)map;
    m[0] = streets;
}

PointNode getMapDestination(MapNode map) {
    void** m = (void**)map;
    return m[1];
}

void setMapDestination(MapNode map, PointNode destination) {
    void** m = (void**)map;
    m[1] = destination;
}

// Añadir calle al mapa
void addStreetToMap(MapNode map, PointNode start, PointNode end) {
    StreetNode newStreet = createStreet(start, end, getMapStreets(map));
    setMapStreets(map, newStreet);
}

// Inicializar SDL y crear ventana
bool initialize(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL no pudo inicializarse! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    *window = SDL_CreateWindow("Simulador de Tráfico Urbano - Quito", 
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                             SCREEN_WIDTH, SCREEN_HEIGHT, 
                             SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("La ventana no pudo crearse! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer no pudo crearse! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    return true;
}