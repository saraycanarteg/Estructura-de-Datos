#pragma once
#include <iostream>
#include <cctype>

using namespace std;

// Declaración anticipada de Lista_Doble como plantilla
template<typename T>
class Lista_Doble;

template<typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente; // Corrige para usar la plantilla
    Nodo<T>* anterior;  // Corrige para usar la plantilla

public:
    // Constructor
    Nodo(T dato);

    // Métodos para dato
    void setDato(T valor);
    T getDato();

    // Métodos para siguiente
    void setSiguiente(Nodo<T>* nodo);
    Nodo<T>* getSiguiente();

    // Métodos para anterior
    void setAnterior(Nodo<T>* nodo);
    Nodo<T>* getAnterior();

    // Clase amiga especificada como plantilla
    friend class Lista_Doble<T>;
};
