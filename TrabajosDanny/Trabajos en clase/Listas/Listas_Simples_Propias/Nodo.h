/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Danny Ayuquina                                      *
 * Fecha de creacion:              28/11/2024                                          *
 * Fecha de modificacion:          28/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

template <typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente; // Corregido: Nodo<T> en lugar de Nodo.

public:
    Nodo(T);
    void set_Dato(T);
    T get_Dato();

    void set_Siguiente(Nodo*); // Corregido: Nodo<T>* en lugar de Nodo*.
    Nodo* get_Siguiente();     // Corregido: Nodo<T>* en lugar de Nodo*.

    friend class ListaSimple; // Parametriza también la amistad con <T>.
};
