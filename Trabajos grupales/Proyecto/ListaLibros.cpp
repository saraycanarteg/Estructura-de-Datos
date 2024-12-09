#include <iostream>
#include "ListaLibros.h"
#include <fstream>
#include <ctime>
#include <sstream>

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
    generarBackup();
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

void ListaLibros::generarBackup() const {
    if (cabeza == nullptr) {
        std::cout << "No hay libros para respaldar." << std::endl;
        return;
    }

    // Obtener la fecha y hora actuales
    std::time_t ahora = std::time(nullptr);
    std::tm* fechaHora = std::localtime(&ahora);

    // Formatear la fecha y hora como "dd.MM.yyyy.HH.mm.ss"
    std::ostringstream nombreArchivo;
    nombreArchivo 
                  << (fechaHora->tm_mday) << "."
                  << (fechaHora->tm_mon + 1) << "."
                  << (fechaHora->tm_year + 1900) << "."
                  << (fechaHora->tm_hour) << "."
                  << (fechaHora->tm_min) << "."
                  << (fechaHora->tm_sec) ;

    // Crear y abrir el archivo
    std::ofstream archivoBackup(nombreArchivo.str());
    if (!archivoBackup.is_open()) {
        std::cerr << "Error al crear el archivo de respaldo." << std::endl;
        return;
    }

    // Escribir los datos de los libros en el archivo
    NodoLibro* actual = cabeza;
    archivoBackup << "Backup de libros (fecha y hora: " 
                  << nombreArchivo.str() << "):\n\n";
    do {
        archivoBackup << "Titulo: " << actual->libro.getTitulo() << "\n";
        archivoBackup << "Autor: " << actual->libro.getAutor().getNombreCompleto() << "\n";
        archivoBackup << "Fecha de publicacion: " << actual->libro.getFechaPublicacion().getFechaComoString() << "\n";
        archivoBackup << "ISBN: " << actual->libro.getIsbn() << "\n";
        archivoBackup << "---\n";
        actual = actual->siguiente;
    } while (actual != cabeza);

    archivoBackup.close();
    std::cout << "Respaldo generado con éxito: " << nombreArchivo.str() << std::endl;
}

void ListaLibros::restaurarBackup(const string& fechaHora) const {
    // Construir el nombre del archivo a buscar
    std::ifstream archivoBackup(fechaHora);
    
    if (!archivoBackup.is_open()) {
        cout << "No se encontró un archivo de respaldo con la fecha y hora ingresada." << endl;
        return;
    }

    cout << "Restaurando libros desde el respaldo...\n";

    string titulo, autor, fecha, isbn;
    while (getline(archivoBackup, titulo) &&
           getline(archivoBackup, autor) &&
           getline(archivoBackup, fecha) &&
           getline(archivoBackup, isbn)) {
        cout << "Título: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Fecha de publicación: " << fecha << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "------" << endl;
    }

    archivoBackup.close();
    cout << "\nRestauración completada con éxito." << endl;
}