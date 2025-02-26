#include "PlanificadorActividades.cpp"

int main() {
    int A[] = {0, 2, 4, 6, 5, 7, 8, 9, 3, 1};
    int B[] = {4, 3, 7, 10, 8, 9, 13, 14, 12, 6};
    int n = sizeof(A) / sizeof(A[0]);
    
    PlanificadorActividades planificador(A, B, n);
    planificador.buscarSolucion();
    planificador.mostrarResultado();
    
    return 0;
}