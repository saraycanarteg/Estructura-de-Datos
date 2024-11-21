
#include "Nodo.h"

using namespace std;

template<typename T>
 Nodo<T>::Nodo(T _dato) {
    dato = _dato;
    siguiente = NULL;
}

template<typename T>
inline void Nodo<T>::setDato(T _dato) {
    dato = _dato;
}

template<typename T>
 T Nodo<T>::getDato() {
    return dato;
}

template<typename T>
 void Nodo<T>::setSiguiente(Nodo* _siguiente) {
    siguiente = _siguiente;
}

template<typename T>
 Nodo<T>* Nodo<T>::getSiguiente() {
    return siguiente;
}

