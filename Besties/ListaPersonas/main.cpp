#include <iostream>
#include "lista.cpp"
#include "persona.cpp"
#include "validaciones.cpp"

using namespace std;

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    Lista<Persona> listaOriginal;
    Lista<Persona> listaModificada; // Lista auxiliar para datos modificados
    int opcion;
    string cedula, apellido, nombre;

    do {
        limpiarPantalla();
        cout << "\n--- Menu ---\n";
        cout << "1. Insertar por cabeza\n";
        cout << "2. Insertar por cola\n";
        cout << "3. Mostrar lista original\n";
        cout << "4. Mostrar lista modificada\n";
        cout << "5. Eliminar caracter\n";
        cout << "6. Reemplazar caracter\n"; // Nueva opción
        cout << "7. Buscar persona\n";
        cout << "8. Eliminar persona\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese cedula: ";
                cin >> cedula;
                cout << "Ingrese apellido: ";
                cin >> apellido;
                cout << "Ingrese nombre: ";
                cin >> nombre;

                if (validarCedula(cedula) && validarTexto(apellido) && validarTexto(nombre)) {
                    listaOriginal.insertarPorCabeza(Persona(cedula, apellido, nombre));
                } else {
                    cout << "Datos invalidos.\n";
                }
                break;

            case 2:
                cout << "Ingrese cedula: ";
                cin >> cedula;
                cout << "Ingrese apellido: ";
                cin >> apellido;
                cout << "Ingrese nombre: ";
                cin >> nombre;

                if (validarCedula(cedula) && validarTexto(apellido) && validarTexto(nombre)) {
                    listaOriginal.insertarPorCola(Persona(cedula, apellido, nombre));
                } else {
                    cout << "Datos invalidos.\n";
                }
                break;

            case 3:
                cout << "\n--- Lista Original ---\n";
                listaOriginal.mostrarLista();
                break;

            case 4:
                cout << "\n--- Lista Modificada ---\n";
                listaModificada.mostrarLista();
                break;

            case 5: {
                char caracter;
                cout << "Ingrese el caracter a eliminar: ";
                cin >> caracter;

                // Crear una copia de la lista original para modificarla
                listaModificada = listaOriginal;
                listaModificada.eliminarCaracter(caracter);

                cout << "Caracter eliminado en la lista modificada.\n";
                break;
            }

            case 6: { // Nueva funcionalidad para reemplazar caracteres
                char original, reemplazo;
                cout << "Ingrese el caracter a reemplazar: ";
                cin >> original;
                cout << "Ingrese el caracter por el cual reemplazar: ";
                cin >> reemplazo;

                // Crear una copia de la lista original para modificarla
                listaModificada = listaOriginal;
                listaModificada.reemplazarCaracter(original, reemplazo);

                cout << "Caracter reemplazado en la lista modificada.\n";
                break;
            }

            case 7:
                cout << "Ingrese la cedula de la persona a buscar: ";
                cin >> cedula;
                if (validarCedula(cedula)) {
                    listaOriginal.buscarPorCedula(cedula);
                } else {
                    cout << "Datos no validos.\n";
                }
                break;

            case 8:
                cout << "Ingrese la cedula de la persona a eliminar: ";
                cin >> cedula;
                if (validarCedula(cedula)) {
                    listaOriginal.eliminarPorCedula(cedula);
                } else {
                    cout << "Datos no validos.\n";
                }
                break;

            case 9:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

        cout << "\nPresione ENTER para continuar...";
        cin.ignore();
        cin.get();
    } while (opcion != 9);

    return 0;
}
