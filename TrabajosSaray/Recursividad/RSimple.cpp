#include <stdio.h>

// Función recursiva para cuenta regresiva
void cuentaRegresiva(int n) {
    // Imprimimos el número actual
    printf("Contando: %d\n", n);
    
    // Caso base: llegamos a cero
    if (n == 0) {
        printf("¡Despegue!\n");
        return;
    }
    
    // Pausa artificial para ver mejor el proceso
    for(long i = 0; i < 200000000; i++); // Pequeña pausa
    
    // Llamada recursiva
    cuentaRegresiva(n - 1);
}

int main() {
    int inicio = 5;  // Empezamos desde 5
    
    printf("Iniciando cuenta regresiva...\n");
    printf("---------------------------\n");
    
    cuentaRegresiva(inicio);
    
    printf("---------------------------\n");
    printf("Fin del programa\n");
    
    return 0;
}