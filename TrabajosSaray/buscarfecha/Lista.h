#ifndef LISTA_H
#define LISTA_H

#include <iostream>
using namespace std;

template <typename T>
class Nodo {
public:
    T data;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(T data) : data(data), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

    // Función auxiliar para copiar una lista
    void copiarLista(const Nodo<T>* otraCabeza);

public:
    Lista();
    ~Lista();

    Lista(const Lista& otra);            // Constructor de copia
    Lista& operator=(const Lista& otra); // Operador de asignación

    void insertarPorCabeza(T data);
    void insertarPorCola(T data);
    void eliminarPorCabeza();
    void mostrarLista() const;
    void mostrarListaInversa() const; // Nueva función para mostrar la lista en orden inverso
    Nodo<T>* get_cabeza() const;
    Nodo<T>* get_cola();
};

#endif
