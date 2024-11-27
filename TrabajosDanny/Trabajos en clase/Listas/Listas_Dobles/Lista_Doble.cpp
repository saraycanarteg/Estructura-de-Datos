#include "Lista_Doble.h"

template<typename T>
Lista_Doble<T>::Lista_Doble() {
    cabeza = nullptr;
    cola = nullptr;
}

template<typename T>
void Lista_Doble<T>::Insertar_cabeza(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (!cabeza) { // Lista vacía
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
        cabeza = nuevo;
    }
}

template<typename T>
void Lista_Doble<T>::Insertar_cola(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (!cola) { // Lista vacía
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
}

template<typename T>
void Lista_Doble<T>::Buscar(T _dato) {
    Nodo<T>* aux = cabeza;
    while (aux) {
        if (aux->getDato() == _dato) {
            cout << "El dato " << _dato << " se encuentra en la lista." << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista." << endl;
}

template<typename T>
void Lista_Doble<T>::Eliminar(T _dato) {
    Nodo<T>* aux = cabeza;
    while (aux) {
        if (aux->getDato() == _dato) {
            if (aux->getAnterior())
                aux->getAnterior()->setSiguiente(aux->getSiguiente());
            else
                cabeza = aux->getSiguiente();

            if (aux->getSiguiente())
                aux->getSiguiente()->setAnterior(aux->getAnterior());
            else
                cola = aux->getAnterior();

            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista." << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista." << endl;
}

template<typename T>
void Lista_Doble<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    while (aux) {
        cout << aux->getDato() << " -> ";
        aux = aux->getSiguiente();
    }
    cout << "NULL" << endl;
}

template<typename T>
void Lista_Doble<T>::MostrarReversa() {
    Nodo<T>* aux = cola;
    while (aux) {
        cout << aux->getDato() << " -> ";
        aux = aux->getAnterior();
    }
    cout << "NULL" << endl;
}
