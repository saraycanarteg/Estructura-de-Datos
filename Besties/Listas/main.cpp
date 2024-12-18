#include <iostream>
#include <limits>
#include "persona.h"
#include "lista_simple.h"
#include "lista_circular.h"
#include "lista_doble.h"

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Función para obtener un ID válido
int obtenerID() {
    int id;
    while (true) {
        std::cout << "Ingrese ID: ";
        if (std::cin >> id) {
            return id;
        }
        std::cout << "ID inválido. Intente de nuevo.\n";
        limpiarBuffer();
    }
}

// Función para obtener un nombre válido
std::string obtenerNombre(const std::string& tipo) {
    std::string nombre;
    while (true) {
        std::cout << "Ingrese " << tipo << ": ";
        std::getline(std::cin >> std::ws, nombre);
        
        if (!nombre.empty()) {
            return nombre;
        }
        std::cout << tipo << " no puede estar vacío. Intente de nuevo.\n";
    }
}

void menuListaBase(ListaBase* lista, const std::string& nombreLista) {
    int subOpcion;
    do {
        std::cout << "\n--- " << nombreLista << " ---\n";
        std::cout << "1. Ingresar Persona\n";
        std::cout << "2. Eliminar Persona\n";
        std::cout << "3. Buscar Persona\n";
        std::cout << "4. Mostrar Lista\n";
        std::cout << "5. Ordenar Lista\n";
        std::cout << "6. Regresar\n";
        std::cout << "Ingrese su opción: ";
        std::cin >> subOpcion;

        switch(subOpcion) {
            case 1: {
                int id = obtenerID();
                limpiarBuffer(); // Limpiar buffer después de obtener ID
                
                std::string nombre = obtenerNombre("nombre");
                std::string apellido = obtenerNombre("apellido");
                
                lista->insertar(Persona(id, nombre, apellido));
                std::cout << "Persona agregada exitosamente.\n";
                break;
            }
            case 2: {
                int id = obtenerID();
                if (lista->eliminar(id)) {
                    std::cout << "Persona eliminada.\n";
                } else {
                    std::cout << "No se encontró la persona.\n";
                }
                break;
            }
            case 3: {
                int id = obtenerID();
                Persona* p = lista->buscar(id);
                if (p) {
                    p->mostrar();
                } else {
                    std::cout << "Persona no encontrada.\n";
                }
                break;
            }
            case 4: {
                lista->mostrar();
                break;
            }
            case 5: {
                lista->ordenar();
                std::cout << "Lista ordenada.\n";
                break;
            }
        }
    } while (subOpcion != 6);
}

void menuPrincipal() {
    ListaSimple listaSimple;
    ListaDoble listaDoble;
    ListaCircular listaCircular;
    int opcion;

    do {
        std::cout << "\n--- MENÚ PRINCIPAL ---\n";
        std::cout << "1. Lista Simple\n";
        std::cout << "2. Lista Doblemente Enlazada\n";
        std::cout << "3. Lista Circular\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese su opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                menuListaBase(&listaSimple, "LISTA SIMPLE");
                break;
            case 2:
                menuListaBase(&listaDoble, "LISTA DOBLEMENTE ENLAZADA");
                break;
            case 3:
                menuListaBase(&listaCircular, "LISTA CIRCULAR");
                break;
        }
    } while (opcion != 4);
}

int main() {
    menuPrincipal();
    return 0;
}