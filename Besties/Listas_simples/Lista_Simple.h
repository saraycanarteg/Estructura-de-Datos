#pragma once
#include "Nodo.h"
#include <string>
#include <sstream>
#include <typeinfo>

using namespace std;

template<typename T>
class Lista_Simple {
private:
    Nodo<T>* cabeza;
public:
    Lista_Simple();
    void Insertar_cabeza(T);
    void Insertar_cola(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    //Lista_Simple<T>* EliminarCaracter(char caracter);
};

// En Lista_Simple.cpp
template <typename T>
void Lista_Simple<T>::Insertar_cola(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}



