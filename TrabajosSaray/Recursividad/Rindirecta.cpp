#include <stdio.h>

// Declaraciones adelantadas
void funcionA(int n);
void funcionB(int n);

// Primera función
void funcionA(int n) {
    if (n >= 0) {
        printf("A(%d) -> ", n);
        funcionB(n - 1);  // Llama a funcionB
    }
}

// Segunda función
void funcionB(int n) {
    if (n >= 0) {
        printf("B(%d) -> ", n);
        funcionA(n - 1);  // Llama a funcionA
    } else {
        printf("Fin\n");
    }
}

int main() {
    printf("Iniciando con n = 3:\n");
    funcionA(3);
    
    printf("\nIniciando con n = 2:\n");
    funcionA(2);
    
    return 0;
}