// animacion.cpp
#include <graphics.h>
#include "animacion.h"

Animacion::Animacion(Juego& juegoRef) : juego(juegoRef) {
    // Configurar fondo azul y color de texto blanco
    setbkcolor(BLUE);
    setcolor(WHITE);
}

void Animacion::dibujarTablero() {
    // Calcular coordenadas para centrar
    int inicioX = (getmaxx() - (10 * 40)) / 2;
    int inicioY = (getmaxy() - (20 * 30)) / 2;

    // Dibujar bordes del tablero
    setcolor(WHITE);
    
    // Borde izquierdo
    line(inicioX, inicioY, inicioX, inicioY + (20 * 30));
    
    // Borde derecho
    line(inicioX + (10 * 40), inicioY, 
         inicioX + (10 * 40), inicioY + (20 * 30));
    
    // Borde inferior
    line(inicioX, inicioY + (20 * 30), 
         inicioX + (10 * 40), inicioY + (20 * 30));
}

void Animacion::dibujarLetra(const Letra& letra) {
    // Calcular coordenadas para centrar
    int inicioX = (getmaxx() - (10 * 40)) / 2;
    int inicioY = (getmaxy() - (20 * 30)) / 2;

    // Dibujar letra en blanco
    setcolor(WHITE);
    char letraStr[2] = {letra.obtenerValor(), '\0'};
    outtextxy(
        inicioX + letra.obtenerPosX() * 40, 
        inicioY + letra.obtenerPosY() * 30, 
        letraStr
    );
}

void Animacion::dibujarMenu() {
    // Dibujar elementos del menú en blanco
    setcolor(WHITE);
}

void Animacion::dibujarPuntaje() {
    // Mostrar puntaje en blanco
    setcolor(WHITE);
    char puntajeStr[20];
    sprintf(puntajeStr, "Puntaje: %d", juego.obtenerPuntaje());
    outtextxy(450, 50, puntajeStr);
}

void Animacion::mostrarGameOver() {
    // Pantalla de fin de juego en blanco sobre fondo azul
    cleardevice();
    setbkcolor(BLUE);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(250, 300, "GAME OVER");
}

void Animacion::dibujarLetrasTablero() {
    // Calcular coordenadas para centrar
    int inicioX = (getmaxx() - (10 * 40)) / 2;
    int inicioY = (getmaxy() - (20 * 30)) / 2;

    // Recorrer todo el tablero
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            Letra* letra = juego.obtenerLetraActual().obtenerPosX() == j && 
                           juego.obtenerLetraActual().obtenerPosY() == i ? 
                           nullptr : juego.obtenerTablero().obtenerLetra(j, i);
            
            if(letra != nullptr) {
                setcolor(WHITE);
                char letraStr[2] = {letra->obtenerValor(), '\0'};
                outtextxy(
                    inicioX + j * 40, 
                    inicioY + i * 30, 
                    letraStr
                );
            }
        }
    }
}