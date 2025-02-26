#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Lista.cpp"

class QuickSort {
public:
    static Nodo* ordenar(Nodo* cabeza);
    
private:
    static Nodo* getTail(Nodo* cabeza);
    static Nodo* partition(Nodo* cabeza, Nodo* fin, Nodo** nuevaCabeza, Nodo** nuevoFin);
    static Nodo* quickSortRecursivo(Nodo* cabeza, Nodo* fin);
};

#endif