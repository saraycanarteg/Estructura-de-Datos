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

void ListaLibros::guardarLibrosEnArchivo() const {
    std::ofstream archivo("libros.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar los libros." << std::endl;
        return;
    }

    NodoLibro* actual = cabeza;
    if (actual == nullptr) {
        archivo << "No hay libros en la biblioteca." << std::endl;
        archivo.close();
        return;
    }

    do {
        archivo << "Titulo: " << actual->libro.getTitulo() << "\n";
        archivo << "Autor: " << actual->libro.getAutor().getNombreCompleto() << "\n";
        archivo << "Fecha de publicacion: " << actual->libro.getFechaPublicacion().getFechaComoString() << "\n";
        archivo << "ISBN: " << actual->libro.getIsbn() << "\n";
        archivo << "---\n";
        actual = actual->siguiente;
    } while (actual != cabeza);

    archivo.close();
    std::cout << "Archivo actualizado: libros.txt" << std::endl;
}

// Registro de libros
void ListaLibros::registrarLibro(const Libro& libro) {
    NodoLibro* nuevoNodo = new NodoLibro(libro);

    if (cabeza == nullptr) {
        // Primer libro
        cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        // Agregar al final de la lista circular
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cabeza->anterior;
        cabeza->anterior->siguiente = nuevoNodo;
        cabeza->anterior = nuevoNodo;
    }

    tamano++;
    guardarLibrosEnArchivo(); // Actualizar archivo después de registrar
}
bool ListaLibros::modificarLibroPorTitulo(const string& titulo, const Libro& nuevoLibro) {
    NodoLibro* actual = cabeza;
    if (actual == nullptr)
        return false;

    do {
        if (actual->libro.getTitulo() == titulo) {
            actual->libro = nuevoLibro;
            guardarLibrosEnArchivo(); // Actualizar archivo después de modificar
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}



// Eliminación de libros
bool ListaLibros::eliminarLibroPorTitulo(const string& titulo) {
    if (cabeza == nullptr) return false;

    NodoLibro* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo) {
            if (actual == cabeza) {
                cabeza = (cabeza->siguiente == cabeza) ? nullptr : cabeza->siguiente;
            }
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
            delete actual;
            tamano--;

            guardarLibrosEnArchivo(); // <-- Llama a este método después de eliminar
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
                cabeza = (cabeza->siguiente == cabeza) ? nullptr : cabeza->siguiente;
            }
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
            delete actual;
            tamano--;
            guardarLibrosEnArchivo(); // Actualizar archivo después de eliminar
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
Libro* ListaLibros::buscarLibroPorTitulo(const string& titulo) {
    if (cabeza == nullptr) return nullptr;

    NodoLibro* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo) {
            return &actual->libro;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
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
    nombreArchivo << "backup_"
                  << (fechaHora->tm_mday) << "."
                  << (fechaHora->tm_mon + 1) << "."
                  << (fechaHora->tm_year + 1900) << "."
                  << (fechaHora->tm_hour) << "."
                  << (fechaHora->tm_min) << "."
                  << (fechaHora->tm_sec) << ".txt";

    // Abrir el archivo en modo append para preservar backups anteriores
    std::ofstream archivoBackup(nombreArchivo.str(), std::ios_base::app);
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
    // Construir el nombre del archivo con prefijo backup_
    string nombreArchivo = "backup_" + fechaHora + ".txt";
    std::ifstream archivoBackup(nombreArchivo);
    
    if (!archivoBackup.is_open()) {
        cout << "No se encontró un archivo de respaldo con la fecha y hora ingresada." << endl;
        return;
    }

    cout << "Restaurando libros desde el respaldo...\n";

    // Ignorar la primera línea de encabezado
    string linea;
    std::getline(archivoBackup, linea);

    // Variables para almacenar datos del libro
    string titulo, autor, fechaPublicacion, isbn;
    
    while (std::getline(archivoBackup, linea)) {
        // Saltar línea de separación
        if (linea == "---") continue;

        if (linea.substr(0, 7) == "Titulo:") {
            titulo = linea.substr(8);
            std::getline(archivoBackup, linea);
            autor = linea.substr(7);
            std::getline(archivoBackup, linea);
            fechaPublicacion = linea.substr(22);
            std::getline(archivoBackup, linea);
            isbn = linea.substr(6);

            cout << "Titulo: " << titulo << endl;
            cout << "Autor: " << autor << endl;
            cout << "Fecha de publicacion: " << fechaPublicacion << endl;
            cout << "ISBN: " << isbn << endl;
            cout << "------" << endl;
        }
    }

    archivoBackup.close();
    cout << "\nRestauración completada con éxito." << endl;
}