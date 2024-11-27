
#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "Persona.h"

using namespace std;

template<typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente;
public:
    Nodo(T);
    Nodo(Persona _dato);
    void setDato(T);
    T getDato();
    void setSiguiente(Nodo*);
    Nodo* getSiguiente();
    friend class ListaSimples;
};

template<>
class Nodo<Persona> {
private:
    Persona dato;
    Nodo<Persona>* siguiente;
public:
    Nodo(Persona _dato) : dato(_dato), siguiente(NULL) {}
    void setDato(Persona _dato) { dato = _dato; }
    Persona getDato() { return dato; }
    void setSiguiente(Nodo<Persona>* _siguiente) { siguiente = _siguiente; }
    Nodo<Persona>* getSiguiente() { return siguiente; }
};

