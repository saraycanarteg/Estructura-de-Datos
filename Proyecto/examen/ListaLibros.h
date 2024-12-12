#ifndef LISTA_LIBROS_H
#define LISTA_LIBROS_H

#include "Libro.h"
#include <string>
#include <fstream>
#include <iomanip> 
#include <ctime>
#include <sstream>
#include <vector>
#include <functional> // Para std::function
using namespace std;

// Nodo para la lista doblemente enlazada circular de Libros
class NodoLibro {
public:
    Libro libro;
    NodoLibro* siguiente;
    NodoLibro* anterior;

    NodoLibro(const Libro& lib); // Constructor del nodo
};

class ListaLibros {
private:
    NodoLibro* cabeza;
    int tamano;

public:
    // Constructor y destructor
    ListaLibros();
    ~ListaLibros();

    // Métodos principales
    void guardarLibrosEnArchivo() const;

    void registrarLibro(const Libro& libro);              // Registrar un nuevo libro
    Libro* buscarLibroPorTitulo(const string& titulo);    // Buscar por título
    Libro* buscarLibroPorIsbn(const string& isbn);        // Buscar por ISBN
    bool eliminarLibroPorTitulo(const string& titulo);    // Eliminar por título
    bool eliminarLibroPorIsbn(const string& isbn);        // Eliminar por ISBN
    bool modificarLibroPorTitulo(const string& titulo, const Libro& nuevoLibro); // Modificar libro
    void buscarLibrosPorAutor(const string& idAutor, ListaLibros& resultados);
    vector<Libro> cargarLibrosDeAutor(const Autor& autor);
    vector<Autor> cargarAutoresDesdeCSV();
    void guardarLibrosDeAutor(const Autor& autor);
    void guardarAutorCSV(const Autor& autor);
   
    // Métodos auxiliares
    void imprimirLibros() const;                          // Imprimir la lista de libros
    int obtenerTamano() const;                            // Obtener el tamaño de la lista
    bool estaVacia() const;                               // Verificar si la lista está vacía
    void generarBackup() const;                           // Generar un backup
    void restaurarBackup(const string& fechaHora) const;  // Restaurar desde un backup
    void retornar_libros_txt();                           // Retornar libros desde un archivo
    void generarArchivoCSV() const; 
    vector<Libro> cargarLibrosDesdeCSV() const;                      // Generar archivo CSV
    void filtrarLibrosPorRangoDeAnios(int anioInicio, int anioFin) const;

};

#endif // LISTA_LIBROS_H