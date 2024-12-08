#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

template<typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente;
public:
    Nodo(T);
    void setDato(T);
    T getDato();
    void setSiguiente(Nodo*);
    Nodo* getSiguiente();
    friend class ListaSimples;
};