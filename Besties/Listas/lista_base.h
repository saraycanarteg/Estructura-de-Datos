#ifndef LISTA_BASE_H
#define LISTA_BASE_H

#include "nodo.h"
#include "persona.h"

class ListaBase {
protected:
    Nodo* cabeza;
    bool esCircular;

    Nodo* partition(Nodo* low, Nodo* high);
    void quickSortUtil(Nodo* low, Nodo* high);
    Nodo* getUltimoNodo();

public:
    ListaBase(bool circular = false);
    virtual ~ListaBase();

    virtual void insertar(const Persona& p) = 0;
    virtual bool eliminar(int id) = 0;
    virtual Persona* buscar(int id) = 0;
    virtual void mostrar() = 0;
    virtual void ordenar() = 0;
};

#endif // LISTA_BASE_H