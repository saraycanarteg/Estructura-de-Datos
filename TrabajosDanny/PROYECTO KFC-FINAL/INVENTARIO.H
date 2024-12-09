#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Inventario{
    string codigo;
    string nombre;
    string cantidad;
};
Inventario elinventario[14];

void mostrarinventario(){
    ifstream arch_inventario;
    string auxiliar, line;
    int j;

	arch_inventario.open("inventarioaux.txt", ios :: in);

	if (arch_inventario.fail ()){
		cout << "No se pudo abrir el inventario";
		exit (1);
	}
    cout<<endl<<"========================================================================="<<endl;
    cout<<"  ************************  DETALLE INVENTARIO  **********************    "<<endl;
    cout<<"========================================================================="<<endl;
    cout<<"CODIGO"<<setw(20)<<"NOMBRE"<<setw(35)<<"CANTIDAD"<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;


    ///Inventario items descripcion
    while (getline (arch_inventario, line)){
		stringstream ss (line);
		getline (ss, auxiliar, ',');
        elinventario[j].codigo=auxiliar;
		getline (ss, auxiliar, ',');
		elinventario[j].nombre=auxiliar;
		getline (ss, auxiliar, ',');
		elinventario[j].cantidad = auxiliar;
		j++;
    }
	arch_inventario.close() ;

	for(j=0;j<14;j++){
        cout<<elinventario[j].codigo<<setw(30)<<elinventario[j].nombre<<setw(30)<<elinventario[j].cantidad<<endl;
	}

}

