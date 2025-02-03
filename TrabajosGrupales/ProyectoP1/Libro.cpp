#include "Libro.h"
#include "Autor.h"
#include "Fecha.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor por defecto
Libro::Libro() : titulo(""), autor(Autor()), fecha_publicacion(Fecha()), isbn("") {}

Libro::Libro(string titulo, Autor autor, Fecha fecha_publicacion, string isbn)
    : titulo(titulo), autor(autor), fecha_publicacion(fecha_publicacion), isbn(isbn) {}

// Getters
string Libro::getTitulo() const { 
    return titulo; 
}

Autor Libro::getAutor() const { 
    return autor; 
}

Fecha Libro::getFechaPublicacion() const { 
    return fecha_publicacion; 
}

string Libro::getIsbn() const { 
    return isbn; 
}

// Setters
void Libro::setTitulo(string titulo) {
    this->titulo = titulo;
}

void Libro::setAutor(Autor autor) {
    this->autor = autor;
}

void Libro::setFechaPublicacion(Fecha fecha_publicacion) {
    this->fecha_publicacion = fecha_publicacion;
}

void Libro::setIsbn(string isbn) {
    this->isbn = isbn;
}

// Sobrecarga del operador de comparación (si es necesario)
bool Libro::operator==(const Libro& otro) const {
    return this->isbn == otro.isbn;
}

void Libro::mostrarDetalles() const {
    cout << "Título: " << titulo << endl;
    cout << "Autor: " << autor.getNombre() << endl;
    cout << "Fecha de Publicación: ";
    fecha_publicacion.mostrarFecha();
    cout << "ISBN: " << isbn << endl;
}