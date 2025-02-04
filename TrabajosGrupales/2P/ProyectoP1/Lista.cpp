#include "Lista.h"
#include "Libro.h"
#include "Autor.h"
#include "Fecha.h"
#include <iostream>
#include <algorithm>
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

template <typename T>
void Lista<T>::registrarLibro() {
    string titulo, isbn;
    Autor autor;
    Fecha fecha;
    
    cout << "Ingrese el título del libro: ";
    getline(cin >> ws, titulo);
    
    cout << "Ingrese el nombre del autor: ";
    string nombre_autor;
    getline(cin, nombre_autor);
    autor.setNombre(nombre_autor);
    
    int dia, mes, anio;
    cout << "Ingrese la fecha de publicación (dia mes año): ";
    cin >> dia >> mes >> anio;
    fecha = Fecha(dia, mes, anio);
    
    cout << "Ingrese el ISBN: ";
    cin >> isbn;
    
    Libro nuevoLibro(titulo, autor, fecha, isbn);
    this->insertarPorCola(nuevoLibro);
    
    cout << "Libro registrado exitosamente." << endl;
}

// Método para buscar libro por título
template <typename T>
void Lista<T>::buscarLibroPorTitulo(string titulo) {
    if (!cabeza) {
        cout << "La lista de libros está vacía." << endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    bool encontrado = false;
    
    do {
        if (actual->data.getTitulo() == titulo) {
            actual->data.mostrarDetalles();
            encontrado = true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    if (!encontrado) {
        cout << "No se encontraron libros con ese título." << endl;
    }
}

// Método para buscar libro por autor
template <typename T>
void Lista<T>::buscarLibroPorAutor(string autor) {
    if (!cabeza) {
        cout << "La lista de libros está vacía." << endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    bool encontrado = false;
    
    do {
        if (actual->data.getAutor().getNombre() == autor) {
            actual->data.mostrarDetalles();
            encontrado = true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    if (!encontrado) {
        cout << "No se encontraron libros de ese autor." << endl;
    }
}

// Método para buscar libro por ISBN
template <typename T>
void Lista<T>::buscarLibroPorIsbn(string isbn) {
    if (!cabeza) {
        cout << "La lista de libros está vacía." << endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    
    do {
        if (actual->data.getIsbn() == isbn) {
            actual->data.mostrarDetalles();
            return;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    cout << "No se encontró un libro con ese ISBN." << endl;
}

// Método para eliminar libro por ISBN
template <typename T>
void Lista<T>::eliminarLibroPorIsbn(string isbn) {
    if (!cabeza) {
        cout << "La lista de libros está vacía." << endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = cola;
    
    do {
        if (actual->data.getIsbn() == isbn) {
            // Si es el único elemento
            if (actual == cabeza && actual == cola) {
                delete cabeza;
                cabeza = cola = nullptr;
                cout << "Libro eliminado exitosamente." << endl;
                return;
            }
            
            // Si es la cabeza
            if (actual == cabeza) {
                cabeza = actual->siguiente;
            }
            
            // Si es la cola
            if (actual == cola) {
                cola = anterior;
            }
            
            // Actualizar enlaces
            anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = anterior;
            
            delete actual;
            cout << "Libro eliminado exitosamente." << endl;
            return;
        }
        
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    cout << "No se encontró un libro con ese ISBN." << endl;
}

// Método para mostrar todos los libros
template <typename T>
void Lista<T>::mostrarLibros() {
    if (!cabeza) {
        cout << "La lista de libros está vacía." << endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    int contador = 1;
    
    do {
        cout << "Libro " << contador++ << ":" << endl;
        actual->data.mostrarDetalles();
        cout << "------------------------" << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

// Método para mostrar libros por autor
template <typename T>
void Lista<T>::mostrarLibrosPorAutor(string autor) {
    if (!cabeza) {
        cout << "La lista de libros está vacía." << endl;
        return;
    }
    
    Nodo<T>* actual = cabeza;
    bool encontrado = false;
    int contador = 1;
    
    do {
        if (actual->data.getAutor().getNombre() == autor) {
            cout << "Libro " << contador++ << ":" << endl;
            actual->data.mostrarDetalles();
            cout << "------------------------" << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    if (!encontrado) {
        cout << "No se encontraron libros de ese autor." << endl;
    }
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