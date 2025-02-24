#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

// Definición de Nodo para representar intersecciones
class Nodo {
public:
    int id;
    Nodo* siguiente;
    Nodo(int id) {
        this->id = id;
        this->siguiente = NULL;
    }
    ~Nodo() {}
};

class Grafo {
    public:
        int numNodos;
        Nodo** listaAdyacencia;
    
        Grafo(int numNodos) {
            this->numNodos = numNodos;
            listaAdyacencia = new Nodo*[numNodos];
            for (int i = 0; i < numNodos; i++) {
                listaAdyacencia[i] = NULL;
            }
        }
    
        void agregarArista(int origen, int destino) {
            Nodo* nuevoNodo = new Nodo(destino);
            nuevoNodo->siguiente = listaAdyacencia[origen];
            listaAdyacencia[origen] = nuevoNodo;
        }
    
        ~Grafo() {
            for (int i = 0; i < numNodos; i++) {
                Nodo* actual = listaAdyacencia[i];
                while (actual) {
                    Nodo* temp = actual;
                    actual = actual->siguiente;
                    delete temp;
                }
            }
            delete[] listaAdyacencia;
        }
    };


    