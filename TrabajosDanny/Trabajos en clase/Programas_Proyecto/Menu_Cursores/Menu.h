// Menu.h
#ifndef MENU_H
#define MENU_H

#include "Lista_Circular.h"
#include <string>
#include <conio.h> // Para manejar el teclado

using namespace std;

template<typename T>
class Menu {
private:
    Lista_Circular<T> menu; // Lista circular para las opciones del menú
public:
    void LlenarMenu(); // Llenar las opciones del menú
    void ImprimirMenu(); // Imprimir el menú
    int EscogerOpcion(); // Navegar por el menú con cursores
};

#endif
