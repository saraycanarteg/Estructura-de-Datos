#ifndef PLANIFICADOR_ACTIVIDADES_H
#define PLANIFICADOR_ACTIVIDADES_H

const int MAX_N = 100;

class PlanificadorActividades {
private:
    int* tiemposInicio;
    int* tiemposFin;
    int numActividades;
    bool solParcial[MAX_N];
    bool solOptima[MAX_N];
    int cardOptima;

    void buscarActividades(int index, int ultimoFin, int cardActual);

public:
    PlanificadorActividades(int A[], int B[], int n);
    void buscarSolucion();
    void mostrarResultado() const;
};

#endif