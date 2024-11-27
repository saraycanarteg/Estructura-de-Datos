#include "Lista_Circular.h"

using namespace std;

template <typename T>
Lista_Circular<T>::Lista_Circular() {
    cabeza = NULL;
}

template <typename T>
void Lista_Circular<T>::Insertar_cabeza(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != cabeza) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
}

template<typename T>
void Lista_Circular<T>::Buscar(T _dato) {
    if (cabeza == NULL) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* aux = cabeza;
    do {
        if (aux->getDato() == _dato) {
            cout << "El dato " << _dato << " se encuentra en la lista." << endl;
            return;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    cout << "El dato " << _dato << " no se encuentra en la lista." << endl;
}

template<typename T>
void Lista_Circular<T>::Eliminar(T _dato) {
    if (cabeza == NULL) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    do {
        if (aux->getDato() == _dato) {
            if (anterior == NULL) { // Eliminando el nodo cabeza
                if (aux->getSiguiente() == cabeza) {
                    cabeza = NULL;
                } else {
                    Nodo<T>* temp = cabeza;
                    while (temp->getSiguiente() != cabeza) {
                        temp = temp->getSiguiente();
                    }
                    cabeza = aux->getSiguiente();
                    temp->setSiguiente(cabeza);
                }
            } else {
                anterior->setSiguiente(aux->getSiguiente());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista." << endl;
            return;
        }
        anterior = aux;
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    cout << "El dato " << _dato << " no se encuentra en la lista." << endl;
}

template<typename T>
void Lista_Circular<T>::Mostrar() {
    if (cabeza == NULL) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* aux = cabeza;
    do {
        cout << aux->getDato() << " -> ";
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    cout << "(vuelve a la cabeza)" << endl;
}
