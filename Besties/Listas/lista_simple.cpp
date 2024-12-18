#include "lista_simple.h"
#include <iostream>
#include <fstream>

ListaSimple::ListaSimple() : ListaBase(false) {}

void ListaSimple::insertar(const Persona& p) {
    Nodo* nuevoNodo = new Nodo(p);
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        Nodo* temp = cabeza;
        while (temp->getSiguiente()) {
            temp = temp->getSiguiente(); 
        }
        temp->setSiguiente(nuevoNodo);
    }
}

bool ListaSimple::eliminar(int id) {
    if (!cabeza) return false;

    if (cabeza->getDato().getId() == id) {
        Nodo* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
        return true;
    }

    Nodo* temp = cabeza;
    while (temp->getSiguiente()) {
        if (temp->getSiguiente()->getDato().getId() == id) {
            Nodo* aEliminar = temp->getSiguiente();
            temp->setSiguiente(aEliminar->getSiguiente());
            delete aEliminar;
            return true;
        }
        temp = temp->getSiguiente();
    }
    return false;
}

Persona* ListaSimple::buscar(int id) {
    Nodo* temp = cabeza;
    while (temp) {
        if (temp->getDato().getId() == id) {
            return &(temp->getDato());
        }
        temp = temp->getSiguiente();
    }
    return nullptr;
}

void ListaSimple::mostrar() {
    Nodo* temp = cabeza;
    while (temp) {
        temp->getDato().mostrar();
        temp = temp->getSiguiente();
    }
}

void ListaSimple::ordenar() {
    if (!cabeza) return;
    
    // Obtener el último nodo
    Nodo* ultimo = getUltimoNodo();
    
    quickSortUtil(cabeza, ultimo);
}

bool ListaSimple::exportarACSV(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    
    // Verificar si se pudo abrir el archivo
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return false;
    }
    
    // Escribir encabezado
    archivo << "ID,Nombre,Apellido\n";
    
    // Recorrer la lista y escribir cada persona
    Nodo* temp = cabeza;
    while (temp) {
        Persona& persona = temp->getDato();
        archivo << persona.getId() << ","
                << persona.getNombre() << ","
                << persona.getApellido() << "\n";
        temp = temp->getSiguiente();
    }
    
    archivo.close();
    std::cout << "Archivo CSV exportado exitosamente: " << nombreArchivo << std::endl;
    return true;
}