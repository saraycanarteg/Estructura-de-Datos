#include <iostream>
#include <conio.h>
#include "Carro.h"
#include "Grafica.h"

using namespace std;

int main() {
    Carro miCarro(10, 10, 1, "rojo");
    Grafica graficos;
    char tecla;
    
    while(true) {
        graficos.limpiarPantalla();
        graficos.dibujarCarro(miCarro);
        
        if (_kbhit()) {
            tecla = _getch();
            switch(tecla) {
                case 'w':
                    miCarro.moverAdelante();
                    break;
                case 's':
                    miCarro.moverAtras();
                    break;
                case 'q':
                    return 0;
            }
        }
    }
    
    return 0;
}