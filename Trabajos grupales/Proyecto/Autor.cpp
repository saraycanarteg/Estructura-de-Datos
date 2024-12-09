#include "Autor.h"

Autor::Autor() : nombre(""), apellido(""), nacionalidad("") {}

Autor::Autor(string nombre, string apellido, string nacionalidad) 
    : nombre(nombre), apellido(apellido), nacionalidad(nacionalidad) {}

// Getters
string Autor::getNombre() const { return nombre; }
string Autor::getApellido() const { return apellido; }
string Autor::getNacionalidad() const { return nacionalidad; }

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

void Autor::setNacionalidad(string nacionalidad) {
    this->nacionalidad = nacionalidad;
}