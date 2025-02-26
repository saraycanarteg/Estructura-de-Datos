#ifndef BUSCADOR_ARRAY_H
#define BUSCADOR_ARRAY_H

class BuscadorArray {
private:
    int* array;
    int size;

public:
    BuscadorArray(int* arr, int n);
    int buscarElementoPosicion(int inf, int sup);
    int obtenerElemento(int posicion) const;
    int obtenerTamanio() const;
};

#endif