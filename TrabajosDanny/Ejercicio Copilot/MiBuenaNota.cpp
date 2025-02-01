/*Crear un programa en c++ para insertar elementos enteros en un árbol de búsqueda binaria*/
#include <iostream>

struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;
    
    Nodo(int valor) : dato(valor), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolBinarioBusqueda {
public:
    ArbolBinarioBusqueda() : raiz(nullptr) {}

    void insertar(int valor) {
        raiz = insertarRecursivo(raiz, valor);
    }

    void enOrden() {
        enOrdenRecursivo(raiz);
    }

private:
    Nodo* raiz;

    Nodo* insertarRecursivo(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }

        if (valor < nodo->dato) {
            nodo->izquierdo = insertarRecursivo(nodo->izquierdo, valor);
        } else if (valor > nodo->dato) {
            nodo->derecho = insertarRecursivo(nodo->derecho, valor);
        }

        return nodo;
    }

    void enOrdenRecursivo(Nodo* nodo) {
        if (nodo != nullptr) {
            enOrdenRecursivo(nodo->izquierdo);
            std::cout << nodo->dato << " ";
            enOrdenRecursivo(nodo->derecho);
        }
    }
};

int main() {
    ArbolBinarioBusqueda arbol;
    arbol.insertar(5);
    arbol.insertar(3);
    arbol.insertar(7);
    arbol.insertar(2);
    arbol.insertar(4);
    arbol.insertar(6);
    arbol.insertar(8);

    std::cout << "Recorrido en orden: ";
    arbol.enOrden();
    std::cout << std::endl;

    return 0;
}