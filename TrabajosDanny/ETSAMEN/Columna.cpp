#include "Columna.h"

Columna::Columna() : cabeza(nullptr), altura(0) {}

void Columna::insertarNumero(int valor) {
    Numero* nuevoNumero = new Numero(valor);
    if (!cabeza) {
        cabeza = nuevoNumero;
    } else {
        Numero* actual = cabeza;
        while (actual->getSiguiente()) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevoNumero);
    }
    altura++;
}

// ...resto de implementaciones de Columna...