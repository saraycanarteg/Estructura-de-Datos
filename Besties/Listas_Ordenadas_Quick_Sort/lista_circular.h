#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include <iostream>
using namespace std;

template <typename T>
class NodoCircular {
public:
    T data;
    NodoCircular* siguiente;
    NodoCircular* anterior;

    NodoCircular(T data) : data(data), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaCircular {
private:
    NodoCircular<T>* cabeza;
    NodoCircular<T>* cola;

    // Función auxiliar para copiar una ListaCircular
    void copiarListaCircular(const NodoCircular<T>* otraCabeza);

    NodoCircular<T>* partitionByCedula(NodoCircular<T>* low, NodoCircular<T>* high);
    NodoCircular<T>* partitionByNombre(NodoCircular<T>* low, NodoCircular<T>* high);
    NodoCircular<T>* partitionByApellido(NodoCircular<T>* low, NodoCircular<T>* high);
    NodoCircular<T>* getLastNode();

    void quicksortCedula(NodoCircular<T>* low, NodoCircular<T>* high);
    void quicksortNombre(NodoCircular<T>* low, NodoCircular<T>* high);
    void quicksortApellido(NodoCircular<T>* low, NodoCircular<T>* high);

public:
    ListaCircular();
    ~ListaCircular();

    ListaCircular(const ListaCircular& otra);            // Constructor de copia
    ListaCircular& operator=(const ListaCircular& otra); // Operador de asignación

    void insertarPorCabeza(T data);
    void insertarPorCola(T data);
    void eliminarPorCabeza();
    void eliminarPorCedula(string cedula);
    void mostrarLista() const;
    void mostrarListaInversa() const; // Nueva función para mostrar la lista en orden inverso
    void eliminarCaracter(char c);
    void reemplazarCaracter(char original, char reemplazo);
    void buscarPorCedula(string cedula);

    void ordenarPorCedula();
    void ordenarPorNombre();
    void ordenarPorApellido();
};

#endif
