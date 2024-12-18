#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <iostream>
using namespace std;

template <typename T>
class Nodo {
public:
    T data;
    Nodo* siguiente;

    Nodo(T data) : data(data), siguiente(nullptr) {}
};
template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;

    // Función auxiliar para copiar una lista
    void copiarLista(const Nodo<T>* otraCabeza);

public:
    Lista();
    ~Lista();

    Lista(const Lista& otra);            // Constructor de copia
    Lista& operator=(const Lista& otra); // Operador de asignación
    Nodo<T>* get_cola();

    void insertarPorCabeza(T data);
    void insertarPorCola(T data);
    void eliminarPorCabeza();
    void eliminarPorCedula(string cedula);
    void mostrarLista() const;
    void eliminarCaracter(char c);
    void reemplazarCaracter(char original, char reemplazo);
    //void buscarEnLista();
    void buscarPorCedula(string cedula);
};


#endif
