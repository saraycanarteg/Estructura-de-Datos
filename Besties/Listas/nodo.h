#ifndef NODO_H
#define NODO_H

#include "persona.h"

class Nodo {
private:
    Persona dato;
    Nodo* siguiente;
    Nodo* anterior;  // Para manejar listas doblemente enlazadas

public:
    // Constructores
    Nodo();
    Nodo(const Persona& p);
    
    // Getters
    Persona getDato() const;
    Nodo* getSiguiente() const;
    Nodo* getAnterior() const;
    
    // Setters
    void setDato(const Persona& p);
    void setSiguiente(Nodo* sig);
    void setAnterior(Nodo* ant);
};

#endif // NODO_H