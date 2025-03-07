#ifndef JUEGO_H
#define JUEGO_H

#include <string>

const int ANCHO_TABLERO = 10;
const int ALTO_TABLERO = 20;

class Letra {
private:
    char valor;
    int posX, posY;

public:
    Letra();
    Letra(char letra);
    Letra(char letra, int x, int y);

    void establecerValor(char letra);
    char obtenerValor() const;
    void moverAbajo();
    void moverIzquierda();
    void moverDerecha();
    void establecerPosX(int x);
    void establecerPosY(int y);
    int obtenerPosX() const;
    int obtenerPosY() const;
};

class Tablero {
private:
    Letra* matriz[ALTO_TABLERO][ANCHO_TABLERO];
    int anchura, altura;

public:
    Tablero();
    ~Tablero();

    bool verificarColision(const Letra& letra);
    void insertarLetra(const Letra& letra);
    bool verificarLineaCompleta(int fila);
    void eliminarFila(int fila);
    void eliminarLetrasIguales(int fila, char letra);
    Letra* obtenerLetra(int x, int y) const;
    void limpiarTablero();
};

class Juego {
private:
    Tablero tablero;
    Letra letraActual;
    int puntaje;
    std::string nombreJugador;

public:
    Juego();
    void iniciarJuego();
    void procesarTecla(int tecla);
    bool verificarFinJuego();
    int obtenerPuntaje() const;
    void generarNuevaLetra();
    Letra obtenerLetraActual() const;
    Tablero& obtenerTablero() { return tablero; }
};

#endif // JUEGO_H