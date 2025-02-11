#ifndef GRAFO_H
#define GRAFO_H

class Nodo {
public:
    int dato;
    Nodo* siguiente;
    Nodo(int d) : dato(d), siguiente(nullptr) {}
};

class ListaEnlazada {
private:
    Nodo* cabeza;
public:
    ListaEnlazada() : cabeza(nullptr) {}
    ~ListaEnlazada();
    void insertar(int dato);
    void limpiar();
    Nodo* getCabeza() const { return cabeza; }
};

class Grafo {
private:
    int numVertices;
    bool dirigido;
    int** matrizAdyacencia;
    ListaEnlazada* listaAdyacencia;
    double* coordX;
    double* coordY;
    
    void limpiarGrafo();
    void inicializarMatriz();
    void liberarMatriz();

public:
    Grafo(int vertices, bool esDirigido);
    ~Grafo();
    void generarGrafoAleatorio();
    void dibujarMatrizGrafica() const;
    void dibujarListaGrafica() const;
    void dibujarGrafo() const;
    bool esDirigido() const { return dirigido; }
};

#endif
