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
        cout << "6. Buscar persona\n";
        cout << "7. Eliminar persona\n";
        cout << "8. Salir\n";
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
            case 6:
                cout << "Ingrese la cedula de la persona a buscar: ";
                cin >> cedula;
                if (validarCedula(cedula)){
                    listaOriginal.buscarPorCedula(cedula);   
                } else {
                    cout <<"Datos no validos"<<endl;
                }
               break;
            case 7:
                cout <<"Ingrese la cedula de la persona a eliminar: ";
                cin >> cedula;
                if (validarCedula(cedula)){
                    listaOriginal.eliminarPorCedula(cedula);   
                } else {
                    cout <<"Datos no validos \n"<<endl;
                }
                break;
            case 8:
                cout <<"Saliendo del programa ... \n";
                break;
            default:
                cout << "Opcion inválida.\n";
        }

        cout << "\nPresione ENTER para continuar...";
        cin.ignore();
        cin.get();
    } while (opcion != 8);

    return 0;
}
