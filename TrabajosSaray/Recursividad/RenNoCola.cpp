#include <stdio.h>

void imprimir(int n) {
    if (n == 0)
        return;
    imprimir(n - 1);  // Llamada recursiva no en cola
    printf("%d ", n); // Acción después de la llamada recursiva
}

int main() {
    int n = 5;
    imprimir(n);
    return 0;
}
