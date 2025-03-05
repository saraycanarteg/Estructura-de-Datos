#include "PlanificadorActividades.h"
#include <iostream>

PlanificadorActividades::PlanificadorActividades(int A[], int B[], int n) {
    tiemposInicio = A;
    tiemposFin = B;
    numActividades = n;
    cardOptima = 0;
    
    for(int i = 0; i < MAX_N; i++) {
        solParcial[i] = false;
        solOptima[i] = false;
    }
}

void PlanificadorActividades::buscarActividades(int index, int ultimoFin, int cardActual) {
    if (cardActual > cardOptima) {
        for (int i = 0; i < numActividades; i++) {
            solOptima[i] = solParcial[i];
        }
        cardOptima = cardActual;
    }
    
    if (index >= numActividades) return;

    if (tiemposInicio[index] >= ultimoFin) {
        solParcial[index] = true;
        buscarActividades(index + 1, tiemposFin[index], cardActual + 1);
        solParcial[index] = false;
    }

    buscarActividades(index + 1, ultimoFin, cardActual);
}

void PlanificadorActividades::buscarSolucion() {
    buscarActividades(0, 0, 0);
}

void PlanificadorActividades::mostrarResultado() const {
    std::cout << "Máximo conjunto de actividades compatibles: ";
    for (int i = 0; i < numActividades; i++) {
        if (solOptima[i]) {
            std::cout << "a" << i << " ";
        }
    }
    std::cout << std::endl;
}