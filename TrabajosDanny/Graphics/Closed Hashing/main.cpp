#include "NReinas.cpp"

int main() {
    int opcion;
    do {
        system("cls");  // Limpia la pantalla en Windows
        cout << "\n=== PROBLEMA DE LAS N REINAS ===\n";
        cout << "1. Resolver problema de N reinas\n";
        cout << "2. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int n;
                cout << "\nIngrese el numero de reinas: ";
                cin >> n;
                if (n < 1 || n > 8) {
                    cout << "Numero invalido." << endl;
                } else {
                    NReinas juego(n);
                    juego.resolver();
                }
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            }
            case 2:
                cout << "Gracias por usar el programa!\n";
                break;
            default:
                cout << "Opcion invalida!\n";
                cout << "Presione Enter para continuar...";
                cin.ignore();
                cin.get();
        }
    } while (opcion != 2);

    return 0;
}