#include <iostream>
#include <algorithm>
#include "Lista_circular.h"
using namespace std;

template <typename T>
ListaCircular<T>::ListaCircular() : cabeza(nullptr), cola(nullptr) {}

template <typename T>
ListaCircular<T>::~ListaCircular() {
    if (!cabeza) return;

    // Romper el enlace circular
    cola->siguiente = nullptr;
    
    while (cabeza != nullptr) {
        NodoCircular<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

template <typename T>
void ListaCircular<T>::insertarPorCabeza(T data) {
    NodoCircular<T>* nuevo = new NodoCircular<T>(data);
    
    if (!cabeza) {
        // Primera inserción
        cabeza = cola = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        // Insertar al principio de la ListaCircular circular
        nuevo->siguiente = cabeza;
        nuevo->anterior = cola;
        cabeza->anterior = nuevo;
        cola->siguiente = nuevo;
        cabeza = nuevo;
    }
}

template <typename T>
void ListaCircular<T>::insertarPorCola(T data) {
    NodoCircular<T>* nuevo = new NodoCircular<T>(data);
    
    if (!cola) {
        // Primera inserción
        cabeza = cola = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        // Insertar al final de la ListaCircular circular
        nuevo->anterior = cola;
        nuevo->siguiente = cabeza;
        cola->siguiente = nuevo;
        cabeza->anterior = nuevo;
        cola = nuevo;
    }
}


template <typename T>
void ListaCircular<T>::eliminarPorCabeza() {
    if (!cabeza) return;

    if (cabeza == cola) {
        // Último elemento
        delete cabeza;
        cabeza = cola = nullptr;
    } else {
        NodoCircular<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        cabeza->anterior = cola;
        cola->siguiente = cabeza;
        delete temp;
    }
}

template <typename T>
void ListaCircular<T>::eliminarPorCedula(string cedula) {
    if (!cabeza) return;

    NodoCircular<T>* actual = cabeza;
    do {
        if (actual->data.getCedula() == cedula) {
            if (actual == cabeza) {
                eliminarPorCabeza();
            } else if (actual == cola) {
                // Si es el último elemento
                cola = actual->anterior;
                cola->siguiente = cabeza;
                cabeza->anterior = cola;
                delete actual;
            } else {
                // Elemento en medio de la ListaCircular
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                delete actual;
            }
            cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
            return;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
}


template <typename T>
void ListaCircular<T>::mostrarLista() const {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    cout << "Lista de personas:" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "| Cédula     | Apellido        | Nombre       |" << endl;
    cout << "---------------------------------------------" << endl;

    NodoCircular<T>* actual = cabeza; // Usa la plantilla <T> correctamente
    do {
        printf("| %-10s | %-15s | %-12s |\n",
               actual->data.getCedula().c_str(),
               actual->data.getApellido().c_str(),
               actual->data.getNombre().c_str());
        actual = actual->siguiente;
    } while (actual != cabeza); // Vuelve a la cabeza cuando termina

    cout << "---------------------------------------------" << endl;
}


template <typename T>
void ListaCircular<T>::mostrarListaInversa() const {
    if (!cola) return;

    NodoCircular<T>* actual = cola;
    do {
        cout << actual->data.getCedula() << " "
             << actual->data.getApellido() << " "
             << actual->data.getNombre() << endl;
        actual = actual->anterior;
    } while (actual != cola);
}

template <typename T>
void ListaCircular<T>::eliminarCaracter(char c) {
    if (!cabeza) return;

    NodoCircular<T>* actual = cabeza;
    do {
        string cedula = actual->data.getCedula();
        cedula.erase(remove(cedula.begin(), cedula.end(), c), cedula.end());
        actual->data.setCedula(cedula);

        string apellido = actual->data.getApellido();
        apellido.erase(remove(apellido.begin(), apellido.end(), c), apellido.end());
        actual->data.setApellido(apellido);

        string nombre = actual->data.getNombre();
        nombre.erase(remove(nombre.begin(), nombre.end(), c), nombre.end());
        actual->data.setNombre(nombre);

        actual = actual->siguiente;
    } while (actual != cabeza);
}


template <typename T>
void ListaCircular<T>::reemplazarCaracter(char original, char reemplazo) {
    if (!cabeza) return;

    NodoCircular<T>* actual = cabeza;
    do {
        string cedula = actual->data.getCedula();
        replace(cedula.begin(), cedula.end(), original, reemplazo);
        actual->data.setCedula(cedula);

        string apellido = actual->data.getApellido();
        replace(apellido.begin(), apellido.end(), original, reemplazo);
        actual->data.setApellido(apellido);

        string nombre = actual->data.getNombre();
        replace(nombre.begin(), nombre.end(), original, reemplazo);
        actual->data.setNombre(nombre);

        actual = actual->siguiente;
    } while (actual != cabeza);
}

template <typename T>
void ListaCircular<T>::buscarPorCedula(string cedula) {
    if (!cabeza) return;

    NodoCircular<T>* actual = cabeza;
    do {
        if (actual->data.getCedula() == cedula) {
            cout << "Persona encontrada:" << endl;
            cout << "Cedula: " << actual->data.getCedula() << endl;
            cout << "Nombre: " << actual->data.getNombre() << endl;
            cout << "Apellido: " << actual->data.getApellido() << endl;
            return;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
}

template <typename T>
ListaCircular<T>::ListaCircular(const ListaCircular& otra) : cabeza(nullptr), cola(nullptr) {
    copiarListaCircular(otra.cabeza);
}

template <typename T>
ListaCircular<T>& ListaCircular<T>::operator=(const ListaCircular& otra) {
    if (this != &otra) {
        while (cabeza != nullptr) {
            eliminarPorCabeza();
        }
        copiarListaCircular(otra.cabeza);
    }
    return *this;
}

template <typename T>
void ListaCircular<T>::copiarListaCircular(const NodoCircular<T>* otraCabeza) {
    if (!otraCabeza) return;

    const NodoCircular<T>* actual = otraCabeza;
    do {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    } while (actual != otraCabeza);
}

// Método para obtener el último nodo de la lista
template <typename T>
NodoCircular<T>* ListaCircular<T>::getLastNode() {
    if (!cabeza) return nullptr;
    return cola;
}

// Método de partición por cédula
template <typename T>
NodoCircular<T>* ListaCircular<T>::partitionByCedula(NodoCircular<T>* low, NodoCircular<T>* high) {
    T pivot = high->data;
    
    NodoCircular<T>* partitionPrev = low ? low->anterior : nullptr;
    NodoCircular<T>* current = low;
    
    do {
        if (current->data.getCedula() <= pivot.getCedula()) {
            partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    } while (current != high->siguiente);
    
    partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
    std::swap(partitionPrev->data, high->data);
    
    return partitionPrev;
}

// Método de partición por nombre
template <typename T>
NodoCircular<T>* ListaCircular<T>::partitionByNombre(NodoCircular<T>* low, NodoCircular<T>* high) {
    T pivot = high->data;
    
    NodoCircular<T>* partitionPrev = low ? low->anterior : nullptr;
    NodoCircular<T>* current = low;
    
    do {
        if (current->data.getNombre() <= pivot.getNombre()) {
            partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    } while (current != high->siguiente);
    
    partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
    std::swap(partitionPrev->data, high->data);
    
    return partitionPrev;
}

// Método de partición por apellido
template <typename T>
NodoCircular<T>* ListaCircular<T>::partitionByApellido(NodoCircular<T>* low, NodoCircular<T>* high) {
    T pivot = high->data;
    
    NodoCircular<T>* partitionPrev = low ? low->anterior : nullptr;
    NodoCircular<T>* current = low;
    
    do {
        if (current->data.getApellido() <= pivot.getApellido()) {
            partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    } while (current != high->siguiente);
    
    partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
    std::swap(partitionPrev->data, high->data);
    
    return partitionPrev;
}

// Método quicksort recursivo por cédula
template <typename T>
void ListaCircular<T>::quicksortCedula(NodoCircular<T>* low, NodoCircular<T>* high) {
    if (high && low != high && low != high->siguiente) {
        NodoCircular<T>* pivot = partitionByCedula(low, high);
        
        // Encontrar el nodo anterior al pivote
        NodoCircular<T>* prevPivot = low;
        while (prevPivot->siguiente != pivot) {
            prevPivot = prevPivot->siguiente;
        }
        
        // Ordenar recursivamente las sublistas
        if (pivot != low) {
            quicksortCedula(low, prevPivot);
        }
        if (pivot->siguiente != high) {
            quicksortCedula(pivot->siguiente, high);
        }
    }
}

// Método quicksort recursivo por nombre
template <typename T>
void ListaCircular<T>::quicksortNombre(NodoCircular<T>* low, NodoCircular<T>* high) {
    if (high && low != high && low != high->siguiente) {
        NodoCircular<T>* pivot = partitionByNombre(low, high);
        
        // Encontrar el nodo anterior al pivote
        NodoCircular<T>* prevPivot = low;
        while (prevPivot->siguiente != pivot) {
            prevPivot = prevPivot->siguiente;
        }
        
        if (pivot != low) {
            quicksortNombre(low, prevPivot);
        }
        if (pivot->siguiente != high) {
            quicksortNombre(pivot->siguiente, high);
        }
    }
}

// Método quicksort recursivo por apellido
template <typename T>
void ListaCircular<T>::quicksortApellido(NodoCircular<T>* low, NodoCircular<T>* high) {
    if (high && low != high && low != high->siguiente) {
        NodoCircular<T>* pivot = partitionByApellido(low, high);
        
        // Encontrar el nodo anterior al pivote
        NodoCircular<T>* prevPivot = low;
        while (prevPivot->siguiente != pivot) {
            prevPivot = prevPivot->siguiente;
        }
        
        if (pivot != low) {
            quicksortApellido(low, prevPivot);
        }
        if (pivot->siguiente != high) {
            quicksortApellido(pivot->siguiente, high);
        }
    }
}

// Métodos públicos para iniciar el ordenamiento
template <typename T>
void ListaCircular<T>::ordenarPorCedula() {
    if (!cabeza) return;
    NodoCircular<T>* last = cola;
    quicksortCedula(cabeza, last);
}

template <typename T>
void ListaCircular<T>::ordenarPorNombre() {
    if (!cabeza) return;
    NodoCircular<T>* last = cola;
    quicksortNombre(cabeza, last);
}

template <typename T>
void ListaCircular<T>::ordenarPorApellido() {
    if (!cabeza) return;
    NodoCircular<T>* last = cola;
    quicksortApellido(cabeza, last);
}
