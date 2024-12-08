#include "Menu.h"
#include <iostream>
#include <conio.h> // Para usar _getch() en la navegación de cursores.

using namespace std;

Menu::Menu() {}

void Menu::LlenarMenu() {
    int numOpciones;
    cout << "¿Cuántas opciones desea agregar al menú? ";
    cin >> numOpciones;
    cin.ignore(); // Para limpiar el buffer del `cin`.

    for (int i = 1; i <= numOpciones; ++i) {
        string opcion;
        cout << "Ingrese la opción " << i << ": ";
        getline(cin, opcion);
        menu.Insertar_cabeza(opcion); // Insertamos las opciones en la lista circular.
    }
}

void Menu::MostrarMenu() {
    cout << "Menú de opciones:\n";
    menu.Mostrar();
}

void Menu::EscogerOpcion() {
    if (menu == NULL) {
        cout << "El menú está vacío. Llene el menú antes de seleccionar una opción." << endl;
        return;
    }

    Nodo<std::string>* actual = menu.getCabeza(); // Comenzar desde la cabeza.
    char tecla;

    do {
        system("cls"); // Limpiar pantalla (en Windows).
        cout << "Use las flechas arriba/abajo para navegar y Enter para seleccionar.\n";

        // Imprimir todas las opciones con un marcador para la opción actual.
        Nodo<std::string>* aux = menu.getCabeza();
        do {
            if (aux == actual) {
                cout << "-> " << aux->getDato() << " <-\n";
            } else {
                cout << "   " << aux->getDato() << "\n";
            }
            aux = aux->getSiguiente();
        } while (aux != menu.getCabeza());

        tecla = _getch();

        if (tecla == 224) { // Detectar tecla especial.
            tecla = _getch();
            if (tecla == 72) { // Flecha arriba.
                actual = menu.getAnterior(actual);
            } else if (tecla == 80) { // Flecha abajo.
                actual = actual->getSiguiente();
            }
        }

    } while (tecla != 13); // Enter para seleccionar.

    cout << "Ha seleccionado: " << actual->getDato() << endl;
}
