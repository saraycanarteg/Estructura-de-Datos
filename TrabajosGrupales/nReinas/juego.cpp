#include "Juego.h"
#include "Constantes.h"
#include <iostream>
#include <conio.h>
#include <graphics.h>
using namespace std;

Juego::Juego() : tablero(nullptr) {}

Juego::~Juego() {
    if(tablero != nullptr) {
        delete tablero;
    }
}

void Juego::inicializarGraficos(int n) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    int windowWidth = 2 * Constantes::MARGIN + n * Constantes::CELL_SIZE;
    int windowHeight = 2 * Constantes::MARGIN + n * Constantes::CELL_SIZE;
    
    initwindow(windowWidth, windowHeight, "Problema N Reinas");
}

bool Juego::preguntarAnimacion() {
    char respuesta;
    cout << "Desea ver la animacion del proceso? (s/n): ";
    cin >> respuesta;
    return (respuesta == 's' || respuesta == 'S');
}

void Juego::iniciar() {
    int n;
    bool entradaValida = false;
    while (!entradaValida) {
        try {
            cout << "Ingrese el tamano del tablero (maximo 8): ";
            string input;
            cin >> input;
            n = stoi(input); 
            if (n >= 1 && n <= 8) {
                entradaValida = true;
            } else {
                cout << "Error: El tamano debe estar entre 1 y 8." << endl;
            }
        } catch (invalid_argument& e) {
            cout << "Error: Por favor ingrese un numero valido." << endl;
        } catch (out_of_range& e) {
            cout << "Error: El numero ingresado esta fuera de rango." << endl;
        }
    }
    
    bool mostrarAnimacion = preguntarAnimacion();
    
    inicializarGraficos(n);
    tablero = new Tablero(n, mostrarAnimacion);
    
    tablero->dibujar();
    if(tablero->resolverNReinas(0)) {
        tablero->dibujar();
        for(int i = 0; i < n; i++) {
            tablero->dibujarReina(*(tablero->getTablero() + i), i);
        }
    }
}

void Juego::mostrarResultado() {
    if(tablero != nullptr) {
        cout << "\nSolucion encontrada!\n";
        cout << "Posiciones de las reinas:\n";
        for(int i = 0; i < tablero->getTamanio(); i++) {
            cout << "Reina " << (i+1) << ": (" << *(tablero->getTablero() + i)+1 << "," << i+1 << ")\n";
        }
    }
    getch();
    closegraph();
}