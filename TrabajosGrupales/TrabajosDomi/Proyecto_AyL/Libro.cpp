#include "Libro.h"

// Constructor por defecto
Libro::Libro() : titulo(""), autor(Autor()), fecha_publicacion(Fecha()), isbn("") {}

// Constructor con parámetros
Libro::Libro(string titulo, Autor autor, Fecha fecha_publicacion, string isbn, string editorial)
    : titulo(titulo), autor(autor), fecha_publicacion(fecha_publicacion), isbn(isbn), editorial(editorial) {}

// Getters
string Libro::getTitulo() const { return titulo; }
Autor Libro::getAutor() const { return autor; }
Fecha Libro::getFechaPublicacion() const { return fecha_publicacion; }
string Libro::getIsbn() const { return isbn; }
string Libro::getEditorial() const { return editorial; }

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

void Libro::setEditorial(string editorial){
    this->editorial = editorial; 
}