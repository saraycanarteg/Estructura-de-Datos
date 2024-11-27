#include "Nodo.h"

using namespace std;

// Constructor
template<typename T>
Nodo<T>::Nodo(T _dato) {
    dato = _dato;
    siguiente = this; // En una lista circular, el siguiente apunta a sí mismo por defecto
}

// Setters y Getters
template<typename T>
inline void Nodo<T>::setDato(T _dato) {
    dato = _dato;
}

template<typename T>
T Nodo<T>::getDato() {
    return dato;
}

template<typename T>
void Nodo<T>::setSiguiente(Nodo<T>* _siguiente) { // Corrige añadiendo <T>
    siguiente = _siguiente;
}

template<typename T>
Nodo<T>* Nodo<T>::getSiguiente() { // Corrige añadiendo <T>
    return siguiente;
}
