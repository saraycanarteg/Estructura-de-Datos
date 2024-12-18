#include "lista_base.h"
#include <iostream>

ListaBase::ListaBase(bool circular) : cabeza(nullptr), esCircular(circular) {}

ListaBase::~ListaBase() {
    // Si la lista no está vacía
    if (!cabeza) return;

    // Para listas circulares
    if (esCircular) {
        Nodo* actual = cabeza;
        do {
            Nodo* temp = actual;
            actual = actual->getSiguiente();
            delete temp;
        } while (actual != cabeza);
    } 
    // Para listas no circulares
    else {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->getSiguiente();
            delete temp;
        }
    }
}

Nodo* ListaBase::getUltimoNodo() {
    if (!cabeza) return nullptr;
    
    Nodo* ultimo = cabeza;
    while (ultimo->getSiguiente()) {
        ultimo = ultimo->getSiguiente();
    }
    return ultimo;
}

Nodo* ListaBase::partition(Nodo* low, Nodo* high) {
    // Usar el último elemento como pivote
    int pivote = high->getDato().getId();
    
    // Nodo anterior al low (punto de inicio de partición)
    Nodo* i = low ? low->getAnterior() : nullptr;
    
    for (Nodo* j = low; j != high; j = j->getSiguiente()) {
        if (j->getDato().getId() <= pivote) {
            // Mover i
            i = (i == nullptr) ? low : i->getSiguiente();
            
            // Intercambiar datos
            Persona temp = i->getDato();
            i->setDato(j->getDato());
            j->setDato(temp);
        }
    }
    
    // Colocar pivote en su posición correcta
    i = (i == nullptr) ? low : i->getSiguiente();
    
    // Intercambiar el pivote
    Persona temp = i->getDato();
    i->setDato(high->getDato());
    high->setDato(temp);
    
    return i;
}

void ListaBase::quickSortUtil(Nodo* low, Nodo* high) {
    // Condición de terminación
    if (high != nullptr && low != high && low != high->getSiguiente()) {
        // Particionar la lista
        Nodo* p = partition(low, high);
        
        // Ordenar lado izquierdo
        quickSortUtil(low, p->getAnterior());
        
        // Ordenar lado derecho
        quickSortUtil(p->getSiguiente(), high);
    }
}