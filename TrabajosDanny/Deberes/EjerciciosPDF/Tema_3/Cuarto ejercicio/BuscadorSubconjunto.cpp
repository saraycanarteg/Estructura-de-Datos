#include "BuscadorSubconjunto.h"
#include <iostream>

BuscadorSubconjunto::BuscadorSubconjunto(int* arr, int n, int s) {
    array = arr;
    size = n;
    sumaObjetivo = s;
    cardOptima = n + 1;
    
    for(int i = 0; i < MAX_N; i++) {
        solParcial[i] = false;
        solOptima[i] = false;
    }
}

void BuscadorSubconjunto::buscarSubconjunto(int index, int sumaActual) {
    if (sumaActual == sumaObjetivo) {
        int cardActual = 0;
        for (int i = 0; i < size; i++) {
            if (solParcial[i]) cardActual++;
        }
        if (cardActual < cardOptima) {
            for (int i = 0; i < size; i++) {
                solOptima[i] = solParcial[i];
            }
            cardOptima = cardActual;
        }
        return;
    }
    
    if (index >= size || sumaActual > sumaObjetivo) {
        return;
    }
    
    solParcial[index] = true;
    buscarSubconjunto(index + 1, sumaActual + array[index]);
    
    solParcial[index] = false;
    buscarSubconjunto(index + 1, sumaActual);
}

void BuscadorSubconjunto::buscarSolucion() {
    buscarSubconjunto(0, 0);
}

void BuscadorSubconjunto::mostrarResultado() const {
    std::cout << "[ ";
    for (int i = 0; i < size; i++) {
        if (solOptima[i]) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << "]" << std::endl;
}