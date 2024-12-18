#include "persona.h"
#include <iostream>

// Constructor por defecto
Persona::Persona() : id(0), nombre(""), apellido("") {}

// Constructor parametrizado
Persona::Persona(int _id, std::string _nombre, std::string _apellido)
    : id(_id), nombre(_nombre), apellido(_apellido) {}

// Getters
int Persona::getId() const { return id; }
std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }

// Setters
void Persona::setId(int _id) { id = _id; }
void Persona::setNombre(std::string _nombre) { nombre = _nombre; }
void Persona::setApellido(std::string _apellido) { apellido = _apellido; }

// Método mostrar
void Persona::mostrar() const {
    std::cout << "ID: " << id << ", Nombre: " << nombre << " " << apellido << std::endl;
}