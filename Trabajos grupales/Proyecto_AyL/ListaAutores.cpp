#include "ListaAutores.h"

NodoAutor::NodoAutor(const Autor& aut) 
    : autor(aut), siguiente(nullptr), anterior(nullptr) {}

ListaAutores::ListaAutores() : cabeza(nullptr), tamano(0) {}

ListaAutores::~ListaAutores() {
    while (cabeza != nullptr) {
        NodoAutor* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaAutores::registrarAutor(const Autor& autor) {
    NodoAutor* nuevoNodo = new NodoAutor(autor);

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cabeza->anterior;
        cabeza->anterior->siguiente = nuevoNodo;
        cabeza->anterior = nuevoNodo;
    }

    tamano++;
}

Autor* ListaAutores::buscarAutorPorId(const string& id) {
    if (cabeza == nullptr) return nullptr;

    NodoAutor* actual = cabeza;
    do {
        if (actual->autor.getId() == id) {
            return &actual->autor;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

bool ListaAutores::eliminarAutorPorId(const string& id) {
    if (cabeza == nullptr) return false;

    NodoAutor* actual = cabeza;
    do {
        if (actual->autor.getId() == id) {
            if (actual == cabeza) {
                cabeza = (cabeza->siguiente == cabeza) ? nullptr : cabeza->siguiente;
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

/*bool ListaAutores::modificarAutorPorId(const string& id, const Autor& nuevoAutor) {
    NodoAutor* actual = cabeza;
    if (actual == nullptr) return false;

    do {
        if (actual->autor.getId() == id) {
            actual->autor = nuevoAutor;
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}*/

void ListaAutores::imprimirAutores() const {
    if (cabeza == nullptr) {
        cout << "No hay autores registrados." << endl;
        return;
    }

    cout << "Autores registrados:" << endl;
    NodoAutor* actual = cabeza;
    do {
        cout << "ID: " << actual->autor.getId() 
             << ", Nombre: " << actual->autor.getNombreCompleto()
             << ", Nacionalidad: " << actual->autor.getNacionalidad() << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

int ListaAutores::obtenerTamano() const {
    return tamano;
}

bool ListaAutores::estaVacia() const {
    return cabeza == nullptr;
}