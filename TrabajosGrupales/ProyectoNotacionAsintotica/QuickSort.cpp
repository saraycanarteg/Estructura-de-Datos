#include "QuickSort.h"

Nodo* QuickSort::getTail(Nodo* cabeza) {
    while (cabeza != nullptr && cabeza->getSiguiente() != nullptr)
        cabeza = cabeza->getSiguiente();
    return cabeza;
}

Nodo* QuickSort::partition(Nodo* cabeza, Nodo* fin, Nodo** nuevaCabeza, Nodo** nuevoFin) {
    Nodo* pivot = fin;
    Nodo* prev = nullptr;
    Nodo* cur = cabeza;
    Nodo* tail = pivot;

    while (cur != pivot) {
        if (cur->getDato() <= pivot->getDato()) {
            if (*nuevaCabeza == nullptr)
                *nuevaCabeza = cur;
            prev = cur;
            cur = cur->getSiguiente();
        } else {
            if (prev)
                prev->setSiguiente(cur->getSiguiente());
            Nodo* tmp = cur->getSiguiente();
            cur->setSiguiente(nullptr);
            tail->setSiguiente(cur);
            tail = cur;
            cur = tmp;
        }
    }

    if (*nuevaCabeza == nullptr)
        *nuevaCabeza = pivot;

    *nuevoFin = tail;
    return pivot;
}

Nodo* QuickSort::quickSortRecursivo(Nodo* cabeza, Nodo* fin) {
    if (!cabeza || cabeza == fin)
        return cabeza;

    Nodo* nuevaCabeza = nullptr;
    Nodo* nuevoFin = nullptr;

    Nodo* pivot = partition(cabeza, fin, &nuevaCabeza, &nuevoFin);

    if (nuevaCabeza != pivot) {
        Nodo* tmp = nuevaCabeza;
        while (tmp->getSiguiente() != pivot)
            tmp = tmp->getSiguiente();
        tmp->setSiguiente(nullptr);

        nuevaCabeza = quickSortRecursivo(nuevaCabeza, tmp);

        tmp = getTail(nuevaCabeza);
        tmp->setSiguiente(pivot);
    }

    pivot->setSiguiente(quickSortRecursivo(pivot->getSiguiente(), nuevoFin));

    return nuevaCabeza;
}

Nodo* QuickSort::ordenar(Nodo* cabeza) {
    if (!cabeza || !cabeza->getSiguiente())
        return cabeza;
        
    return quickSortRecursivo(cabeza, getTail(cabeza));
}