#include <stdio.h>

// Función recursiva en cola para sumar los números de 1 a n
int suma_tail(int n, int acumulador) {
    if (n == 0)
        return acumulador;
    return suma_tail(n - 1, acumulador + n);
}

// Función de ayuda para iniciar la recursión en cola
int suma(int n) {
    return suma_tail(n, 0);
}

int main() {
    int n = 5;
    printf("La suma de los numeros de 1 a %d es: %d\n", n, suma(n));
    return 0;
}
