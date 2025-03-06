#include "Numero.h"

Numero::Numero(int val) : valor(val), siguiente(nullptr) {}

int Numero::getValor() const { 
    return valor; 
}

void Numero::setSiguiente(Numero* num) { 
    siguiente = num; 
}

Numero* Numero::getSiguiente() const { 
    return siguiente; 
}