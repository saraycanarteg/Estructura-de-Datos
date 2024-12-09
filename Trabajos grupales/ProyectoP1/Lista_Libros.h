#ifndef LISTA_LIBROS_H
#define LIBROS_LISTA

#include "Libro.h"S
using namespace std;

// Nodo para la lista doblemente enlazada circular de Libros
class NodoLibro {
public:
    Libro libro;
    NodoLibro* siguiente;
    NodoLibro* anterior;

    NodoLibro(const Libro& lib);
};

class ListaLibros {
private:
    NodoLibro* cabeza;
    int tamano;

public:
    // Constructor
    ListaLibros();
    // Destructor
    ~ListaLibros();

    void registrarLibro(const Libro& libro);
    Libro* buscarLibroPorTitulo(const string& titulo);
    Libro* buscarLibroPorIsbn(const string& isbn);

    bool eliminarLibroPorTitulo(const string& titulo);
    bool eliminarLibroPorIsbn(const string& isbn);

    void imprimirLibros() const;

    int obtenerTamano() const;
    bool estaVacia() const;
};

#endif 