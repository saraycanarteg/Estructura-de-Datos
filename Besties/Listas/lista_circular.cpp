#include "lista_circular.h"
#include <iostream>

ListaCircular::ListaCircular() : ListaBase(true) {}

void ListaCircular::insertar(const Persona& p) {
    Nodo* nuevoNodo = new Nodo(p);
    
    if (!cabeza) {
        cabeza = nuevoNodo;
        cabeza->setSiguiente(cabeza);
    } else {
        Nodo* temp = cabeza;
        while (temp->getSiguiente() != cabeza) {
            temp = temp->getSiguiente();
        }
        temp->setSiguiente(nuevoNodo);
        nuevoNodo->setSiguiente(cabeza);
    }
}

bool ListaCircular::eliminar(int id) {
    if (!cabeza) return false;

    // Caso especial: primer nodo
    if (cabeza->getDato().getId() == id) {
        if (cabeza->getSiguiente() == cabeza) {
            // Solo un nodo
            delete cabeza;
            cabeza = nullptr;
            return true;
        }

        // Más de un nodo
        Nodo* ultimoNodo = cabeza;
        while (ultimoNodo->getSiguiente() != cabeza) {
            ultimoNodo = ultimoNodo->getSiguiente();
        }

        Nodo* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        ultimoNodo->setSiguiente(cabeza);
        delete temp;
        return true;
    }

    // Buscar en el resto de la lista
    Nodo* actual = cabeza;
    do {
        if (actual->getSiguiente()->getDato().getId() == id) {
            Nodo* aEliminar = actual->getSiguiente();
            actual->setSiguiente(aEliminar->getSiguiente());
            delete aEliminar;
            return true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return false;
}

Persona* ListaCircular::buscar(int id) {
    if (!cabeza) return nullptr;

    Nodo* actual = cabeza;
    do {
        if (actual->getDato().getId() == id) {
            return &(actual->getDato());
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return nullptr;
}

void ListaCircular::mostrar() {
    if (!cabeza) {
        std::cout << "Lista vacía.\n";
        return;
    }

    Nodo* actual = cabeza;
    do {
        actual->getDato().mostrar();
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

void ListaCircular::ordenar() {
    if (!cabeza || cabeza->getSiguiente() == cabeza) return;
    
    // Encontrar el último nodo
    Nodo* ultimo = cabeza;
    while (ultimo->getSiguiente() != cabeza) {
        ultimo = ultimo->getSiguiente();
    }
    
    quickSortUtil(cabeza, ultimo);
}