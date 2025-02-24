#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX_LINE 1000
#define MAX_PATH 256
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ENTER 13

// Estructura para las opciones del menú
typedef struct {
    const char* titulo;
    void (*funcion)();
} OpcionMenu;

// Prototipos de funciones
void leerPrototipos(const char* ruta);
void escanearArchivo();
void graficarFuncion();
void mostrarMenu(OpcionMenu opciones[], int numOpciones);
void limpiarPantalla();
void gotoxy(int x, int y);
int count(const char* str, char c);
void extraerCodigoFuncion(const char* nombreFuncion, const char* rutaArchivoCpp, char* codigoFuncion, size_t maxLen);

#endif