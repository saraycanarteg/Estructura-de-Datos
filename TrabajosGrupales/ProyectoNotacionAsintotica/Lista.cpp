#include <iostream>
#include "Lista.h"

Lista::Lista() {
    cabeza = nullptr;
    longitud = 0;
}

Lista::~Lista() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

void Lista::insertarInicio(int valor) {
    Nodo* nuevo = new Nodo(valor);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
    longitud++;
}

void Lista::insertarFinal(int valor) {
    Nodo* nuevo = new Nodo(valor);
    
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        Nodo* actual = cabeza;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    longitud++;
}

void Lista::mostrar() const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->getDato() << " ";
        actual = actual->getSiguiente();
    }
    std::cout << std::endl;
}

Nodo* Lista::getCabeza() const {
    return cabeza;
}

void Lista::setCabeza(Nodo* nuevaCabeza) {
    cabeza = nuevaCabeza;
}

int Lista::getLongitud() const {
    return longitud;
}
