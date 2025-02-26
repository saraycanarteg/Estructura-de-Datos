#include "BuscadorSubconjunto.cpp"

int main() {
    int L[] = {1, 3, 5, 6, 7, 9};
    int s = 13;
    int n = sizeof(L) / sizeof(L[0]);
    
    BuscadorSubconjunto buscador(L, n, s);
    buscador.buscarSolucion();
    buscador.mostrarResultado();
    
    return 0;
}