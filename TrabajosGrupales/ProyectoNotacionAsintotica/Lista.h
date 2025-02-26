#ifndef LISTA_H
#define LISTA_H

#include "Nodo.cpp"

class Lista {
private:
    Nodo* cabeza;
    int longitud;
    
public:
    Lista();
    ~Lista();
    void insertarInicio(int valor);
    void insertarFinal(int valor);
    void mostrar() const;
    Nodo* getCabeza() const;
    void setCabeza(Nodo* nuevaCabeza);
    int getLongitud() const;
};

#endif