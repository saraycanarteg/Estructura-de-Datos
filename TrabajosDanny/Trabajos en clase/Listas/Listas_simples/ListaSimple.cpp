#include "ListaSimple.h"
// ListaSimple.cpp (implementación)
template<typename T>
ListaSimple<T>::ListaSimple() : cabeza(nullptr), longitud(0) {}

template<typename T>
ListaSimple<T>::~ListaSimple() {
    vaciar();
}

template<typename T>
Nodo<T>* ListaSimple<T>::getCabeza() const {
    return cabeza;
}

template<typename T>
int ListaSimple<T>::getLongitud() const {
    return longitud;
}

template<typename T>
void ListaSimple<T>::setCabeza(Nodo<T>* nuevaCabeza) {
    cabeza = nuevaCabeza;
}

template<typename T>
void ListaSimple<T>::insertar(T valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    if (estaVacia()) {
        cabeza = nuevo;
    } else {
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    longitud++;
}

template<typename T>
void ListaSimple<T>::insertarInicio(T valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    longitud++;
}

template<typename T>
void ListaSimple<T>::insertarPosicion(T valor, int posicion) {
    if (posicion < 0 || posicion > longitud) {
        return;
    }
    
    if (posicion == 0) {
        insertarInicio(valor);
        return;
    }
    
    Nodo<T>* nuevo = new Nodo<T>(valor);
    Nodo<T>* actual = cabeza;
    for (int i = 0; i < posicion - 1; i++) {
        actual = actual->siguiente;
    }
    
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    longitud++;
}

template<typename T>
T ListaSimple<T>::buscar(T valor) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == valor) {
            return actual->dato;
        }
        actual = actual->siguiente;
    }
    throw "Elemento no encontrado";
}

template<typename T>
bool ListaSimple<T>::existe(T valor) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == valor) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

template<typename T>
void ListaSimple<T>::mostrar() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato << " -> ";
        actual = actual->siguiente;
    }
    std::cout << "nullptr" << std::endl;
}

template<typename T>
bool ListaSimple<T>::eliminar(T valor) {
    if (estaVacia()) {
        return false;
    }
    
    if (cabeza->dato == valor) {
        return eliminarInicio();
    }
    
    Nodo<T>* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->dato != valor) {
        actual = actual->siguiente;
    }
    
    if (actual->siguiente == nullptr) {
        return false;
    }
    
    Nodo<T>* temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    delete temp;
    longitud--;
    return true;
}

template<typename T>
bool ListaSimple<T>::eliminarInicio() {
    if (estaVacia()) {
        return false;
    }
    
    Nodo<T>* temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp;
    longitud--;
    return true;
}

template<typename T>
bool ListaSimple<T>::eliminarPosicion(int posicion) {
    if (posicion < 0 || posicion >= longitud) {
        return false;
    }
    
    if (posicion == 0) {
        return eliminarInicio();
    }
    
    Nodo<T>* actual = cabeza;
    for (int i = 0; i < posicion - 1; i++) {
        actual = actual->siguiente;
    }
    
    Nodo<T>* temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    delete temp;
    longitud--;
    return true;
}

template<typename T>
bool ListaSimple<T>::estaVacia() const {
    return cabeza == nullptr;
}

template<typename T>
void ListaSimple<T>::vaciar() {
    while (!estaVacia()) {
        eliminarInicio();
    }
}
