// ListaSimple.h
#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include <iostream>

template<typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

template<typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;
    int longitud;

public:
    // Constructor y Destructor
    ListaSimple();
    ~ListaSimple();
    
    // Getters
    Nodo<T>* getCabeza() const;
    int getLongitud() const;
    
    // Setters
    void setCabeza(Nodo<T>* nuevaCabeza);
    
    // Operaciones CRUD
    void insertar(T valor);             // Create
    void insertarInicio(T valor);
    void insertarPosicion(T valor, int posicion);
    
    T buscar(T valor) const;            // Read
    bool existe(T valor) const;
    void mostrar() const;
    
    bool eliminar(T valor);             // Delete
    bool eliminarInicio();
    bool eliminarPosicion(int posicion);
    
    // Otras operaciones
    bool estaVacia() const;
    void vaciar();
};


#endif // LISTA_SIMPLE_H