#include <iostream>
#include "QuickSort.cpp"

using namespace std;

int main()
{
    Lista lista;
    int opcion;

    do
    {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Cargar datos de prueba" << endl;
        cout << "2. Ingresar datos manualmente" << endl;
        cout << "3. Mostrar listas" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            lista = Lista(); // Limpiar lista anterior
            lista.insertarFinal(64);
            lista.insertarFinal(34);
            lista.insertarFinal(25);
            lista.insertarFinal(12);
            lista.insertarFinal(22);
            lista.insertarFinal(11);
            lista.insertarFinal(90);
            cout << "Datos de prueba cargados exitosamente!" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 2:
        {
            lista = Lista(); // Limpiar lista anterior
            int n, valor;
            cout << "Ingrese cantidad de números: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Ingrese número " << (i + 1) << ": ";
                cin >> valor;
                lista.insertarFinal(valor);
            }
            cout << "Datos ingresados exitosamente!" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 3:
        {
            if (lista.getCabeza() == nullptr)
            {
                cout << "La lista está vacía. Por favor ingrese datos primero." << endl;
                system("pause");
                system("cls");
                break;
            }
            // Mostrar lista original
            cout << "Lista original: ";
            lista.mostrar();

            // Crear copia para ordenar
            Lista listaOrdenada;
            Nodo *temp = lista.getCabeza();
            while (temp != nullptr)
            {
                listaOrdenada.insertarFinal(temp->getDato());
                temp = temp->getSiguiente();
            }

            // Ordenar y mostrar
            listaOrdenada.setCabeza(QuickSort::ordenar(listaOrdenada.getCabeza()));
            cout << "Lista ordenada: ";
            listaOrdenada.mostrar();
            system("pause");
            system("cls");
            break;
        }

        case 4:
            cout << "¡Gracias por usar el programa!" << endl;
            system("pause");

            break;

        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            system("pause");
            system("cls");
        }

    } while (opcion != 4);

    return 0;
}