#include "BuscadorArray.h"

BuscadorArray::BuscadorArray(int* arr, int n) {
    array = arr;
    size = n;
}

int BuscadorArray::buscarElementoPosicion(int inf, int sup) {
    int mitad = (inf + sup) / 2;

    if (mitad == array[mitad]){
        return mitad;
        
    }else if (inf >= sup){
        return -1;
        
    }else if (mitad < array[mitad]){
        return buscarElementoPosicion(inf, mitad - 1);
    
    } else {
        return buscarElementoPosicion(mitad + 1, sup);
    }
}

int BuscadorArray::obtenerElemento(int posicion) const {
    return array[posicion];
}

int BuscadorArray::obtenerTamanio() const {
    return size;
}