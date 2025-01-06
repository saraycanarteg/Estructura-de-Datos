#include "ListaAutores.h"
#include <fstream>
#include <algorithm>

NodoAutor::NodoAutor(const Autor& aut) 
    : autor(aut), siguiente(nullptr), anterior(nullptr) {}

ListaAutores::ListaAutores() : cabeza(nullptr), tamano(0) {}

ListaAutores::~ListaAutores() {
    while (cabeza != nullptr) {
        NodoAutor* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaAutores::registrarAutor(const Autor& autor) {
    NodoAutor* nuevoNodo = new NodoAutor(autor);

    // Si la lista está vacía
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        // Insertar ordenadamente por ID
        NodoAutor* actual = cabeza;
        bool insertado = false;
        
        do {
            if (autor.getId() < actual->autor.getId()) {
                // Insertar antes del nodo actual
                nuevoNodo->siguiente = actual;
                nuevoNodo->anterior = actual->anterior;
                actual->anterior->siguiente = nuevoNodo;
                actual->anterior = nuevoNodo;
                
                if (actual == cabeza) {
                    cabeza = nuevoNodo;  // Actualizar la cabeza si insertamos al inicio
                }
                insertado = true;
                break;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
        
        // Si no se insertó (es el mayor), insertar al final
        if (!insertado) {
            nuevoNodo->siguiente = cabeza;
            nuevoNodo->anterior = cabeza->anterior;
            cabeza->anterior->siguiente = nuevoNodo;
            cabeza->anterior = nuevoNodo;
        }
    }
    tamano++;
    generarArchivoCSV();
}


Autor* ListaAutores::buscarAutorPorId(const string& id) {
    if (cabeza == nullptr) return nullptr;
    
    // Si solo hay un elemento
    if (cabeza->siguiente == cabeza) {
        return (cabeza->autor.getId() == id) ? &(cabeza->autor) : nullptr;
    }

    NodoAutor* inicio = cabeza;
    NodoAutor* fin = cabeza->anterior;
    
    while (inicio != fin && inicio->anterior != fin) {
        // Encontrar el nodo medio
        NodoAutor* medio = inicio;
        NodoAutor* temp = inicio;
        int count = 0;
        do {
            temp = temp->siguiente;
            count++;
            if (count % 2 == 0) {
                medio = medio->siguiente;
            }
        } while (temp != fin->siguiente);
        
        if (medio->autor.getId() == id) {
            return &(medio->autor);
        }
        
        if (id < medio->autor.getId()) {
            fin = medio->anterior;
        } else {
            inicio = medio->siguiente;
        }
    }
    
    // Verificar los nodos restantes
    if (inicio->autor.getId() == id) return &(inicio->autor);
    if (fin->autor.getId() == id) return &(fin->autor);
    
    return nullptr;
}

bool ListaAutores::eliminarAutorPorId(const string& id) {
    Autor* autorAEliminar = buscarAutorPorId(id);
    if (autorAEliminar == nullptr) return false;

    // Encontrar el nodo que contiene el autor
    NodoAutor* actual = cabeza;
    do {
        if (&(actual->autor) == autorAEliminar) {
            // Si es el único nodo
            if (actual->siguiente == actual) {
                cabeza = nullptr;
            } else {
                if (actual == cabeza) {
                    cabeza = actual->siguiente;
                }
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            delete actual;
            tamano--;
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

/*bool ListaAutores::modificarAutorPorId(const string& id, const Autor& nuevoAutor) {
    NodoAutor* actual = cabeza;
    if (actual == nullptr) return false;

    do {
        if (actual->autor.getId() == id) {
            actual->autor = nuevoAutor;
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}*/

void ListaAutores::imprimirAutores() const {
    if (cabeza == nullptr) {
        cout << "No hay autores registrados." << endl;
        return;
    }

    cout << "Autores registrados:" << endl;
    NodoAutor* actual = cabeza;
    do {
        cout << "ID: " << actual->autor.getId() 
             << ", Nombre: " << actual->autor.getNombreCompleto()
             << ", Nacionalidad: " << actual->autor.getNacionalidad() << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

int ListaAutores::obtenerTamano() const {
    return tamano;
}

bool ListaAutores::estaVacia() const {
    return cabeza == nullptr;
}

void ListaAutores::generarArchivoCSV() const {
    std::ofstream archivoCSV("autores.csv");
    if (!archivoCSV.is_open()) {
        std::cerr << "Error al abrir el archivo CSV para guardar los autores." << std::endl;
        return;
    }

    // Escribir encabezados del CSV
    archivoCSV << "ID,Nombre Completo,Nacionalidad\n";

    // Si la lista está vacía, no hacer nada más
    if (cabeza == nullptr) {
        archivoCSV.close();
        return;
    }

    // Recorrer la lista circular y escribir cada autor
    NodoAutor* actual = cabeza;
    do {
        // Obtener datos usando los métodos de la clase Autor
        std::string id = actual->autor.getId();
        std::string nombreCompleto = actual->autor.getNombreCompleto();
        std::string nacionalidad = actual->autor.getNacionalidad();
        
        // Reemplazar comas con punto y coma si existen
        std::replace(id.begin(), id.end(), ',', ';');
        std::replace(nombreCompleto.begin(), nombreCompleto.end(), ',', ';');
        std::replace(nacionalidad.begin(), nacionalidad.end(), ',', ';');

        archivoCSV << id << ","
                   << nombreCompleto << ","
                   << nacionalidad << "\n";

        actual = actual->siguiente;
    } while (actual != cabeza);

    archivoCSV.close();
    std::cout << "Archivo CSV de autores actualizado: autores.csv" << std::endl;
}