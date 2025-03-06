#ifndef COLUMNA_H
#define COLUMNA_H

#include "Numero.h"

class Columna {
private:
    Numero* cabeza;
    int altura;

public:
    Columna();
    void insertarNumero(int valor);
    bool eliminarNumerosIguales();
    void alinearIzquierda();
    int getAltura() const;
    Numero* getCabeza() const;
};

#endif