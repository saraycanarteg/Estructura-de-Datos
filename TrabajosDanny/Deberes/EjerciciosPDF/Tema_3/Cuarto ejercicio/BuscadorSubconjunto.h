#ifndef BUSCADOR_SUBCONJUNTO_H
#define BUSCADOR_SUBCONJUNTO_H

const int MAX_N = 100;

class BuscadorSubconjunto {
private:
    int* array;
    int size;
    int sumaObjetivo;
    bool solParcial[MAX_N];
    bool solOptima[MAX_N];
    int cardOptima;

    void buscarSubconjunto(int index, int sumaActual);

public:
    BuscadorSubconjunto(int* arr, int n, int s);
    void buscarSolucion();
    void mostrarResultado() const;
};

#endif