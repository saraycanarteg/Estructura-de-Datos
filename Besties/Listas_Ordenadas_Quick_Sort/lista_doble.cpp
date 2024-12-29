#include <iostream>
#include <algorithm>
#include "lista_doble.h"

using namespace std;

template <typename T>
ListaDoble<T>::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

template <typename T>
ListaDoble<T>::~ListaDoble() {
    while (cabeza != nullptr) {
        eliminarPorCabeza();
    }
}

template <typename T>
void ListaDoble<T>::insertarPorCabeza(T data) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(data);
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
}

template <typename T>
void ListaDoble<T>::insertarPorCola(T data) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(data);
    if (!cola) {
        cabeza = cola = nuevo;
    } else {
        nuevo->anterior = cola;
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

template <typename T>
void ListaDoble<T>::eliminarPorCabeza() {
    if (!cabeza) return;

    NodoDoble<T>* temp = cabeza;
    if (cabeza == cola) {
        cabeza = cola = nullptr;
    } else {
        cabeza = cabeza->siguiente;
        cabeza->anterior = nullptr;
    }
    delete temp;
}

template <typename T>
void ListaDoble<T>::eliminarPorCedula(string cedula) {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.getCedula() == cedula) {
            if (actual == cabeza) {
                eliminarPorCabeza();
            } else if (actual == cola) {
                cola = cola->anterior;
                cola->siguiente = nullptr;
                delete actual;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                delete actual;
            }
            cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
}

template <typename T>
void ListaDoble<T>::mostrarLista() const {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    cout << "Lista de personas:" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "| Cédula     | Apellido        | Nombre       |" << endl;
    cout << "---------------------------------------------" << endl;

    NodoDoble<T>* actual = cabeza; // Usa la plantilla <T> correctamente
    while (actual != nullptr) {
        printf("| %-10s | %-15s | %-12s |\n",
               actual->data.getCedula().c_str(),
               actual->data.getApellido().c_str(),
               actual->data.getNombre().c_str());
        actual = actual->siguiente;
    }

    cout << "---------------------------------------------" << endl;
}


template <typename T>
void ListaDoble<T>::mostrarListaInversa() const {
    NodoDoble<T>* actual = cola;
    while (actual != nullptr) {
        cout << actual->data.getCedula() << " "
             << actual->data.getApellido() << " "
             << actual->data.getNombre() << endl;
        actual = actual->anterior;
    }
}

template <typename T>
void ListaDoble<T>::eliminarCaracter(char c) {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
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
    }
}

template <typename T>
void ListaDoble<T>::reemplazarCaracter(char original, char reemplazo) {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
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
    }
}

template <typename T>
void ListaDoble<T>::buscarPorCedula(string cedula) {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.getCedula() == cedula) {
            cout << "Persona encontrada:" << endl;
            cout << "Cedula: " << actual->data.getCedula() << endl;
            cout << "Nombre: " << actual->data.getNombre() << endl;
            cout << "Apellido: " << actual->data.getApellido() << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
}

template <typename T>
ListaDoble<T>::ListaDoble(const ListaDoble& otra) : cabeza(nullptr), cola(nullptr) {
    copiarListaDoble(otra.cabeza);
}

template <typename T>
ListaDoble<T>& ListaDoble<T>::operator=(const ListaDoble& otra) {
    if (this != &otra) {
        while (cabeza != nullptr) {
            eliminarPorCabeza();
        }
        copiarListaDoble(otra.cabeza);
    }
    return *this;
}

template <typename T>
void ListaDoble<T>::copiarListaDoble(const NodoDoble<T>* otraCabeza) {
    const NodoDoble<T>* actual = otraCabeza;
    while (actual != nullptr) {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    }
}

// Método para obtener el último nodo de la lista
template <typename T>
NodoDoble<T>* ListaDoble<T>::getLastNode() {
    if (!cabeza) return nullptr;
    
    NodoDoble<T>* actual = cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    return actual;
}

// Método de partición por cédula
template <typename T>
NodoDoble<T>* ListaDoble<T>::partitionByCedula(NodoDoble<T>* low, NodoDoble<T>* high) {
    T pivot = high->data;
    
    NodoDoble<T>* partitionPrev = low ? low->anterior : nullptr;
    NodoDoble<T>* current = low;
    
    while (current != high) {
        if (current->data.getCedula() <= pivot.getCedula()) {
            partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    }
    
    partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
    std::swap(partitionPrev->data, high->data);
    
    return partitionPrev;
}

// Método de partición por nombre
template <typename T>
NodoDoble<T>* ListaDoble<T>::partitionByNombre(NodoDoble<T>* low, NodoDoble<T>* high) {
    T pivot = high->data;
    
    NodoDoble<T>* partitionPrev = low ? low->anterior : nullptr;
    NodoDoble<T>* current = low;
    
    while (current != high) {
        if (current->data.getNombre() <= pivot.getNombre()) {
            partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    }
    
    partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
    std::swap(partitionPrev->data, high->data);
    
    return partitionPrev;
}

// Método de partición por apellido
template <typename T>
NodoDoble<T>* ListaDoble<T>::partitionByApellido(NodoDoble<T>* low, NodoDoble<T>* high) {
    T pivot = high->data;
    
    NodoDoble<T>* partitionPrev = low ? low->anterior : nullptr;
    NodoDoble<T>* current = low;
    
    while (current != high) {
        if (current->data.getApellido() <= pivot.getApellido()) {
            partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    }
    
    partitionPrev = partitionPrev ? partitionPrev->siguiente : low;
    std::swap(partitionPrev->data, high->data);
    
    return partitionPrev;
}

// Método quicksort recursivo por cédula
template <typename T>
void ListaDoble<T>::quicksortCedula(NodoDoble<T>* low, NodoDoble<T>* high) {
    if (high && low != high && low != high->siguiente) {
        NodoDoble<T>* pivot = partitionByCedula(low, high);
        
        // Encontrar el nodo anterior al pivote
        NodoDoble<T>* prevPivot = low;
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
void ListaDoble<T>::quicksortNombre(NodoDoble<T>* low, NodoDoble<T>* high) {
    if (high && low != high && low != high->siguiente) {
        NodoDoble<T>* pivot = partitionByNombre(low, high);
        
        // Encontrar el nodo anterior al pivote
        NodoDoble<T>* prevPivot = low;
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
void ListaDoble<T>::quicksortApellido(NodoDoble<T>* low, NodoDoble<T>* high) {
    if (high && low != high && low != high->siguiente) {
        NodoDoble<T>* pivot = partitionByApellido(low, high);
        
        // Encontrar el nodo anterior al pivote
        NodoDoble<T>* prevPivot = low;
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
void ListaDoble<T>::ordenarPorCedula() {
    if (!cabeza) return;
    NodoDoble<T>* last = getLastNode();
    quicksortCedula(cabeza, last);
}

template <typename T>
void ListaDoble<T>::ordenarPorNombre() {
    if (!cabeza) return;
    NodoDoble<T>* last = getLastNode();
    quicksortNombre(cabeza, last);
}

template <typename T>
void ListaDoble<T>::ordenarPorApellido() {
    if (!cabeza) return;
    NodoDoble<T>* last = getLastNode();
    quicksortApellido(cabeza, last);
}
