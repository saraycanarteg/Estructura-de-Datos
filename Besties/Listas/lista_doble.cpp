#include "lista_doble.h"
#include <iostream>

ListaDoble::ListaDoble() : ListaBase(false) {}

void ListaDoble::insertar(const Persona& p) {
    Nodo* nuevoNodo = new Nodo(p);
    
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        Nodo* temp = cabeza;
        while (temp->getSiguiente()) {
            temp = temp->getSiguiente();
        }
        temp->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(temp);
    }
}

bool ListaDoble::eliminar(int id) {
    if (!cabeza) return false;

    // Caso especial: primer nodo
    if (cabeza->getDato().getId() == id) {
        Nodo* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        
        if (cabeza) {
            cabeza->setAnterior(nullptr);
        }
        
        delete temp;
        return true;
    }

    // Buscar en el resto de la lista
    Nodo* actual = cabeza;
    while (actual) {
        if (actual->getDato().getId() == id) {
            // Ajustar enlaces del nodo anterior
            if (actual->getAnterior()) {
                actual->getAnterior()->setSiguiente(actual->getSiguiente());
            }
            
            // Ajustar enlaces del nodo siguiente
            if (actual->getSiguiente()) {
                actual->getSiguiente()->setAnterior(actual->getAnterior());
            }
            
            delete actual;
            return true;
        }
        actual = actual->getSiguiente();
    }

    return false;
}

Persona* ListaDoble::buscar(int id) {
    Nodo* temp = cabeza;
    while (temp) {
        if (temp->getDato().getId() == id) {
            return &(temp->getDato());
        }
        temp = temp->getSiguiente();
    }
    return nullptr;
}

void ListaDoble::mostrar() {
    Nodo* temp = cabeza;
    while (temp) {
        temp->getDato().mostrar();
        temp = temp->getSiguiente();
    }
}

void ListaDoble::ordenar() {
    if (!cabeza) return;
    
    // Obtener el último nodo
    Nodo* ultimo = getUltimoNodo();
    
    quickSortUtil(cabeza, ultimo);
}