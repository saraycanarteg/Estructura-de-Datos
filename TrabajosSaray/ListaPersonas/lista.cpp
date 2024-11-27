#include "lista.h"
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
Lista<T>::Lista() : cabeza(nullptr) {}

template <typename T>
Lista<T>::~Lista() {
    while (cabeza != nullptr) {
        eliminarPorCabeza();
    }
}

template <typename T>
void Lista<T>::insertarPorCabeza(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void Lista<T>::insertarPorCola(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

template <typename T>
void Lista<T>::eliminarPorCabeza() {
    if (!cabeza) return;
    Nodo<T>* temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp;
}

template <typename T>
void Lista<T>::mostrarLista() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->data.getCedula() << " "
             << actual->data.getApellido() << " "
             << actual->data.getNombre() << endl;
        actual = actual->siguiente;
    }
}

template <typename T>
void Lista<T>::eliminarCaracter(char c) {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        // Eliminar carácter de cédula, apellido y nombre
        string cedula = actual->data.getCedula();
        cedula.erase(remove(cedula.begin(), cedula.end(), c), cedula.end());
        actual->data.setCedula(cedula);

        string apellido = actual->data.getApellido();
        apellido.erase(remove(apellido.begin(), apellido.end(), c), apellido.end());
        actual->data.setApellido(apellido);

        string nombre = actual->data.getNombre();
        nombre.erase(remove(nombre.begin(), nombre.end(), c), nombre.end());
        actual->data.setNombre(nombre);

        actual = actual->siguiente;
    }
}
template <typename T>
Lista<T>::Lista(const Lista& otra) : cabeza(nullptr) {
    copiarLista(otra.cabeza);
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista& otra) {
    if (this != &otra) {
        while (cabeza != nullptr) {
            eliminarPorCabeza();
        }
        copiarLista(otra.cabeza);
    }
    return *this;
}

template <typename T>
void Lista<T>::copiarLista(const Nodo<T>* otraCabeza) {
    const Nodo<T>* actual = otraCabeza;
    while (actual != nullptr) {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    }
}

