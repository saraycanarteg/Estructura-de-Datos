#include "nodo.h"

// Constructor por defecto
Nodo::Nodo() : dato(Persona()), siguiente(nullptr), anterior(nullptr) {}

// Constructor con Persona
Nodo::Nodo(const Persona& p) : dato(p), siguiente(nullptr), anterior(nullptr) {}

// Getters
Persona Nodo::getDato() const { return dato; }
Nodo* Nodo::getSiguiente() const { return siguiente; }
Nodo* Nodo::getAnterior() const { return anterior; }

// Setters
void Nodo::setDato(const Persona& p) { dato = p; }
void Nodo::setSiguiente(Nodo* sig) { siguiente = sig; }
void Nodo::setAnterior(Nodo* ant) { anterior = ant; }