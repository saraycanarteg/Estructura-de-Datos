#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "MENU.h"
#include "INVENTARIO.h"

using namespace std;

int main(){
	int opcion1, opcion2;

	do{
        fflush(stdin);
        Extraer_Inventario();
        cout << "\n==================================================="
             << "\n| \t BIENVENIDO AL SISTEMA DE KFC             |"
             << "\n==================================================="
             << endl;
        cout << "\n==================================================="<< endl;
        cout << "| SELECCIONE USUARIO:                             |"<<
        endl << "| \t 1. ADMINISTRADOR                         |"<<
        endl << "| \t 2. CONSUMIDOR                            |";
        cout << "\n==================================================="<< endl;
        cout << "OPCION: ";
        cin >> opcion1;
        cout << endl;
        cin.ignore();
       system("cls");

            switch (opcion1)
            {
                case 1:
                            do{
                            fflush(stdin);
                            Extraer_Inventario();
                            cout << "\n==================================================="
                                 << "\n  | \t   OPCIONES DE ADMINISTRADOR            |"
                                 << "\n===================================================" << endl;

                            cout << "\n==================================================="<< endl;
                            cout << "| 1. Agregar Nuevo Producto                       |"<<
                            endl << "| 2. Mostrar inventario                           |"<<
                            endl << "| 3. Busqueda de facturas                         |";
                            cout << "\n==================================================="<< endl;
                            cout << "OPCION: ";
                            cin >> opcion2;
                            cout << endl;
                            cin.ignore();
                                switch (opcion2)
                                {
                                case 1:
                                    system("cls");
                                    agregarProducto();;
                                    break;
                                case 2:
                                    system("cls");
                                    mostrarinventario();
                                    break;

                                case 3:
                                    system("cls");
                                    Busqueda_Facturas();
                                    break;

                                default:
                                    cout << "\n\nOPCION NO VALIDA" << endl;
                                    break;
                                }
                            system("pause");
                            system("cls");
                            }while(opcion1<1 || opcion1>3);
                            break;
                case 2:
                            system("cls");
                             cout<<endl<<"\n========================================================================="
                                     << "\n| \t\t\t PROCESO DE COMPRA                               |"
                                     << "\n=========================================================================" << endl;
                            ventaproducto();
                            break;
                default:
                            cout << "\n\nOPCION NO VALIDA" << endl;
                            break;
            }
            system("cls");
    }while(true);

    return 0;
}
