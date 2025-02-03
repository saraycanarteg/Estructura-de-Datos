#include "Autor.h"

Autor::Autor() {}

Autor::Autor(string nombre, string apellido, string id, string nacionalidad)
    : nombre(nombre), apellido(apellido), id(id), nacionalidad(nacionalidad) {}

string Autor::getNombre() const {
    return nombre;
}

string Autor::getApellido() const {
    return apellido;
}

string Autor::getNombreCompleto() const {
    return nombre + " " + apellido;
}

string Autor::getId() const {
    return id;
}

string Autor::getNacionalidad() const {
    return nacionalidad;
}

void Autor::setNombre(string nombre) {
    this->nombre = nombre;
}

void Autor::setApellido(string apellido) {
    this->apellido = apellido;
}

void Autor::setId(string id) {
    this->id = id;
}

void Autor::setNacionalidad(string nacionalidad) {
    this->nacionalidad = nacionalidad;
}
