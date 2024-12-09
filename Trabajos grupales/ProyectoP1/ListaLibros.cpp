#include <iostream>
#include "ListaLibros.h"

// Constructor
ListaLibros::ListaLibros() : cabeza(nullptr), tamano(0) {}

NodoLibro::NodoLibro(const Libro& lib)
    : libro(lib), siguiente(nullptr), anterior(nullptr) {}

// Destructor
ListaLibros::~ListaLibros() {
    // Eliminar todos los nodos de la lista
    while (cabeza != nullptr) {
        NodoLibro* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Registro de libros
void ListaLibros::registrarLibro(const Libro& libro) {
    NodoLibro* nuevoNodo = new NodoLibro(libro);

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cabeza->anterior;
        cabeza->anterior->siguiente = nuevoNodo;
        cabeza->anterior = nuevoNodo;
        cabeza = nuevoNodo;
    }

    tamano++;
}

// Búsqueda de libros
Libro* ListaLibros::buscarLibroPorTitulo(const string& titulo) {
    if (cabeza == nullptr)
        return nullptr;

    NodoLibro* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo)
            return &(actual->libro);
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

Libro* ListaLibros::buscarLibroPorIsbn(const string& isbn) {
    if (cabeza == nullptr)
        return nullptr;

    NodoLibro* actual = cabeza;
    do {
        if (actual->libro.getIsbn() == isbn)
            return &(actual->libro);
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

// Eliminación de libros
bool ListaLibros::eliminarLibroPorTitulo(const string& titulo) {
    if (cabeza == nullptr)
        return false;

    NodoLibro* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo) {
            if (actual == cabeza) {
                cabeza = cabeza->siguiente;
            }
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
            delete actual;
            tamano--;
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

bool ListaLibros::eliminarLibroPorIsbn(const string& isbn) {
    if (cabeza == nullptr)
        return false;

    NodoLibro* actual = cabeza;
    do {
        if (actual->libro.getIsbn() == isbn) {
            if (actual == cabeza) {
                cabeza = cabeza->siguiente;
            }
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
            delete actual;
            tamano--;
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

// Impresión de libros
void ListaLibros::imprimirLibros() const {
    if (cabeza == nullptr) {
        cout << "No hay libros en la biblioteca." << endl;
        return;
    }

    cout << "Libros en la biblioteca:" << endl;
    NodoLibro* actual = cabeza;
    do {
        cout << "Titulo: " << actual->libro.getTitulo() << endl;
        cout << "Autor: " << actual->libro.getAutor().getNombreCompleto() << endl;
        cout << "Fecha de publicacion: " << actual->libro.getFechaPublicacion().getFechaComoString() << endl;
        cout << "ISBN: " << actual->libro.getIsbn() << endl;
        cout << "---" << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

// Métodos adicionales
int ListaLibros::obtenerTamano() const {
    return tamano;
}

bool ListaLibros::estaVacia() const {
    return cabeza == nullptr;
}