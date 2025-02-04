#include "Lista.h"
#include <iostream>

using namespace std;

template <typename T>
Lista<T>::Lista() : cabeza(nullptr), cola(nullptr) {}

template <typename T>
Lista<T>::~Lista() {
    if (!cabeza) return;

    // Romper el enlace circular
    cola->siguiente = nullptr;
    
    while (cabeza != nullptr) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

template <typename T>
Nodo<T>* Lista<T>::get_cabeza(){
    return cabeza;
}

template <typename T>
Nodo<T>* Lista<T>::get_cola(){
    return cola;
}

template <typename T>
void Lista<T>::insertarPorCabeza(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
    
    if (!cabeza) {
        // Primera inserción
        cabeza = cola = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        // Insertar al principio de la lista circular
        nuevo->siguiente = cabeza;
        nuevo->anterior = cola;
        cabeza->anterior = nuevo;
        cola->siguiente = nuevo;
        cabeza = nuevo;
    }
}

template <typename T>
void Lista<T>::insertarPorCola(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
    
    if (!cola) {
        // Primera inserción
        cabeza = cola = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        // Insertar al final de la lista circular
        nuevo->anterior = cola;
        nuevo->siguiente = cabeza;
        cola->siguiente = nuevo;
        cabeza->anterior = nuevo;
        cola = nuevo;
    }
}


template <typename T>
void Lista<T>::eliminarPorCabeza() {
    if (!cabeza) return;

    if (cabeza == cola) {
        // Último elemento
        delete cabeza;
        cabeza = cola = nullptr;
    } else {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        cabeza->anterior = cola;
        cola->siguiente = cabeza;
        delete temp;
    }
}

template <typename T>
void Lista<T>::mostrarLista() const {
    if (!cabeza) return;

    Nodo<T>* actual = cabeza;
    do {
        cout << actual->data << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

template <typename T>
void Lista<T>::mostrarListaInversa() const {
    if (!cola) return;
    
    Nodo<T>* actual = cola;
    do {
        cout << actual->data<< endl;
        actual = actual->anterior;
    } while (actual != cola);
}


template <typename T>
Lista<T>::Lista(const Lista& otra) : cabeza(nullptr), cola(nullptr) {
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
    if (!otraCabeza) return;

    const Nodo<T>* actual = otraCabeza;
    do {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    } while (actual != otraCabeza);
}

/*
// Método para guardar libros en un archivo de texto
template <typename T>
void Lista<T>::guardarLibrosEnArchivo(string listaLibros) {
    ofstream archivo(listaLibros);
    
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    
    if (!cabeza) {
        archivo.close();
        cout << "No hay libros para guardar." << endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    
    do {
        archivo << "Título: " << actual->data.getTitulo() << endl;
        archivo << "Autor: " << actual->data.getAutor().getNombre() << endl;
        archivo << "Fecha Publicación: " << actual->data.getFechaPublicacion().getFechaComoString() << endl;
        archivo << "ISBN: " << actual->data.getIsbn() << endl;
        archivo << "------------------------" << endl;
        
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    archivo.close();
    cout << "Libros guardados en " << listaLibros << " exitosamente." << endl;
}*/