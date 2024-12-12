#ifndef LISTA_AUTORES_H
#define LISTA_AUTORES_H

#include "Autor.h"
#include "Libro.h"
#include <iostream>
#include <string>
using namespace std;

class NodoAutor {
public:
    Autor autor;
    NodoAutor* siguiente;
    NodoAutor* anterior;

    NodoAutor(const Autor& aut);
};

class ListaAutores {
private:
    NodoAutor* cabeza;
    int tamano;

public:
    // Constructor y destructor
    ListaAutores();
    ~ListaAutores();

    // Métodos principales
    void registrarAutor(const Autor& autor);
    Autor* buscarAutorPorId(const string& id);
    bool eliminarAutorPorId(const string& id);
    //bool modificarAutorPorId(const string& id, const Autor& nuevoAutor) const;

    // Métodos auxiliares
    void imprimirAutores() const;
    int obtenerTamano() const;
    bool estaVacia() const;
    void generarArchivoCSV() const;
};

#endif // LISTA_AUTORES_H