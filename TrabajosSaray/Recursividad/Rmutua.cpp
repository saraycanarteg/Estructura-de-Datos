#include <stdio.h>

// Declaraciones adelantadas
void ping(int n);
void pong(int n);

// Jugador 1 dice "ping"
void ping(int n) {
    if (n > 0) {
        printf("Ping -> %d\n", n);
        pong(n - 1);
    }
}

// Jugador 2 dice "pong"
void pong(int n) {
    if (n > 0) {
        printf("Pong -> %d\n", n);
        ping(n - 1);
    }
}

int main() {
    printf("Iniciando juego con 4 turnos\n");
    ping(4);
    return 0;
}
