#include "Autor.h"

Autor::Autor() : nombre(""), apellido("") {}

Autor::Autor(string nombre, string apellido) 
    : nombre(nombre), apellido(apellido) {}

// Getters
string Autor::getNombre() const { return nombre; }
string Autor::getApellido() const { return apellido; }

string Autor::getNombreCompleto() const {
    return nombre + " " + apellido;
}

// Setters
void Autor::setNombre(string nombre) {
    this->nombre = nombre;
}

void Autor::setApellido(string apellido) {
    this->apellido = apellido;
}