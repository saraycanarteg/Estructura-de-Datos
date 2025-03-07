#include <graphics.h>
#include <conio.h>
#include "juego.h"
#include "animacion.h"

int main() {
    // Inicializar ventana gráfica con fondo azul
    initwindow(800, 600, "Tetris de Letras");
    setbkcolor(BLUE);
    cleardevice();

    // Configurar texto
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    
    // Dibujar título
    outtextxy(250, 200, "TETRIS DE LETRAS");
    
    // Instrucciones
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(200, 300, "Instrucciones:");
    outtextxy(200, 330, "Flechas Izquierda/Derecha: Mover letra");
    outtextxy(200, 360, "Flecha Abajo: Caida rapida");
    outtextxy(200, 390, "Espacio: Colocar letra");
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(250, 450, "Presiona ESPACIO para iniciar");

    // Esperar tecla de inicio
    while(true) {
        if(kbhit()) {
            int tecla = getch();
            if(tecla == ' ') {
                cleardevice();
                
                Juego juegoTetris;
                Animacion animacion(juegoTetris);
                
                // Dibujar tablero
                animacion.dibujarTablero();
                
                // Contador para caída automática
                int contadorCaida = 0;
                
                // Bucle principal de juego
                while(!juegoTetris.verificarFinJuego()) {
                    // Caída automática cada cierto tiempo
                    contadorCaida++;
                    if(contadorCaida >= 30) {  // Reducir el valor para caída más rápida
                        juegoTetris.procesarTecla(80);  // Tecla de caída abajo
                        contadorCaida = 0;
                    }
                    
                    // Procesar entrada de teclado
                    if(kbhit()) {
                        int tecla = getch();
                        juegoTetris.procesarTecla(tecla);
                    }
                    
                    // Dibujar estado actual
                    cleardevice();
                    animacion.dibujarTablero();
                    animacion.dibujarLetrasTablero();  // Nuevo método para dibujar todas las letras
                    animacion.dibujarLetra(juegoTetris.obtenerLetraActual());
                    animacion.dibujarPuntaje();
                    
                    // Controlar velocidad de juego
                    delay(50);
                }
                
                // Mostrar pantalla de game over
                animacion.mostrarGameOver();
                
                // Esperar tecla para salir
                getch();
                break;
            }
        }
    }

    closegraph();
    return 0;
}