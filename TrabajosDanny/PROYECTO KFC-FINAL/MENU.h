#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "Facturacion.h"
#include "Pilas.h"
#include <queue>

using namespace std;

string auxcodigo;
int cantidad;
float total=0;
float total2=0;
bool encontrado = false;

struct Descripcion_Items{
    int Item[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    string Nom_Item[14];
    string Codigo[14];
};
Descripcion_Items Items[20];
Descripcion_Items Items_total;
Descripcion_Items Aux_Item;

struct NuevoProducto {
	string codigo;
	string nombre;
	float precio;
	string descripcion;
};
NuevoProducto productos[20];

struct VentaAux {
  string nombre;
  float precio;
  int cant;
  float subtotal;
};
queue<VentaAux> colaVentas;


string Convert(float number){
    ostringstream buff;
    buff<<number;
    return buff.str();
}

int Cont_Inventario(){

    int cont_invent=0;

    ifstream Invent;
    string linea;
    Invent.open("menuproductos.txt", ios::in);

    while(getline(Invent, linea)){
        cont_invent++;
    }

    Invent.close();
    return cont_invent;

}

void Extraer_Inventario(){
    ifstream arch_inventario;
    string line, auxiliar;

    ifstream inventarioaux;
    string line2, auxiliar2;

    int contt=Cont_Inventario();

	arch_inventario.open("Descripcion_inventario.txt", ios :: in);

	if (arch_inventario.fail ()){
		cout << "No se pudo abrir el inventario";
		exit (1);
	}

    inventarioaux.open("inventarioaux.txt", ios::in);

	if (inventarioaux.fail ()){
		cout << "No se pudo abrir el inventarioaux";
		exit (1);
	}

    int j=0;
    ///Inventario items descripcion
    while(getline(arch_inventario, line)){
        stringstream ss (line);
        for(int k=0;k<14;k++){
            getline (ss, auxiliar, ',');
            Items[j].Item[k] = stoi(auxiliar);
        }
        j++;
    }
    arch_inventario.close();

    ///Inventario aux (total)
    j=0;
    while (getline (inventarioaux, line2)){
		stringstream ss (line2);
		getline (ss, auxiliar2, ',');
		Items_total.Codigo[j]=auxiliar2;
		getline (ss, auxiliar2, ',');
		Items_total.Nom_Item[j]=auxiliar2;
		getline (ss, auxiliar2, ',');
		Items_total.Item[j] = stoi(auxiliar2);
		j++;
    }
	inventarioaux.close() ;
}

void mostrarMenu() {

  int numProductos = Cont_Inventario();

  ifstream arch_menu ("menuproductos.txt");

  if (arch_menu .is_open()) {
    cout<<endl<<"========================================================================="<<endl;
    cout<<"   \t\t\t********  MENU  ********    "<<endl;
    cout<<"========================================================================="<<endl;
    cout<<"CODIGO"<<setw(20)<<"NOMBRE"<<setw(35)<<"PRECIO"<<setw(30)<<endl;
    cout<<"-------------------------------------------------------------------------";


   	for (int i = 0; i < numProductos; i++){
        arch_menu >> productos[i].codigo
        >> productos[i].nombre
        >> productos[i].precio
        >> productos[i].descripcion;
	}
	for (int i = 0; i < numProductos; i++){
        cout <<endl<< left << "  " << productos[i].codigo << "\t\t "
        << setw(15)<< left << productos[i].nombre<< "\t"
        <<setw(23)<<right<< productos[i].precio
        <<endl
        <<"-------------------------------------------------------------------------";
	}

    arch_menu .close();
  } else {
    cout << "Error al abrir el archivo menuproductos.txt" << endl;
  }
}

void Resta_Inventario(Nodo *&pila, int &n,int &cant){
    int j, k;
    int contt = Cont_Inventario();
    string aux;

    while(pila!=NULL){
        Sacar_Pila(pila,n,cant);

        for(j=0;j<14;j++){
            Items_total.Item[j] = Items_total.Item[j] - (cant*(Items[n].Item[j]));
        }

    }

    ofstream ModInvent ;
    ModInvent.open("inventarioaux.txt", ios::out);

    if(ModInvent.fail()){
        cout<<"Nel"<<endl;
    }

    for(k=0;k<14;k++){
        aux=Convert(Items_total.Item[k]);
        ModInvent<<Items_total.Codigo[k]+","<<Items_total.Nom_Item[k]+","<<aux+"\n";
    }

    ModInvent.close();

    cin.ignore();
}

void Cancelacion_Orden(string identificacion, int op){
    ofstream fact;
    string line;

    if(op==1){
        fact.open("H:\\FDP\\PROYECTO KFC-FINAL\\Facturas\\"+identificacion+".txt", ios::app);
        fact<<"FACTURA CANCELADA"<<"\n";
    }else{
        ifstream nfact;
        nfact.open("N_Factura.txt", ios::in);
        getline(nfact, line);
        nfact.close();
        fact.open("H:\\FDP\\PROYECTO KFC-FINAL\\Consumidor final\\"+line+".txt", ios::app);
        fact<<"FACTURA CANCELADA"<<"\n";
    }
    fact.close();
    cout<<"ORDEN CANCELADA."<<endl;
}

void ventaproducto() {
  Nodo *pila=NULL;
  int n;

  char respuesta='S', conf;

  ofstream Venta_Producto;
  Venta_Producto.open("Venta_Producto.txt", ios::out);
  Venta_Producto << "PRODUCTO" << setw(5) << "\t" << "CANTIDAD" << setw(5)
               << "\t" << "PRECIO" << setw(5) << "\t" << "SUBTOTAL" << endl;

  do{
      mostrarMenu();
      cout<<endl<<"========================================================================="<<endl;
      cout << endl << "Ingrese el codigo del producto: ";
      cin >> auxcodigo;

      bool encontrado = false;

      for (int i = 0; i < Cont_Inventario(); i++) {
        if (productos[i].codigo == auxcodigo) {
          n=i;
          encontrado = true;

          cout << "Cantidad: ";
          cin >> cantidad;
          Agregar_Pila(pila, n, cantidad);

          float subtotal = productos[i].precio * cantidad;
          VentaAux aux;

            aux.nombre = productos[i].codigo;
            aux.precio = productos[i].precio;
            aux.cant = cantidad;
            aux.subtotal = subtotal;
            colaVentas.push(aux);

          total += subtotal;
          total2 = total*1.12;

          cout<<endl<<"========================================================================="<<endl;
          cout << "\n\nProducto: " << productos[i].nombre << endl;
          cout << "Cantidad: " << cantidad << endl;
          cout << "Subtotal: $" << subtotal << endl;
          cout<<endl<<"========================================================================="<<endl;

           Venta_Producto <<" "<< aux.nombre << "\t\t" << setw(15) << left << aux.cant << setw(15)
               << left << aux.precio << setw(15) << left << aux.subtotal << endl;



            cout << endl<<"¿Desea anadir otro producto? (S/N): ";
            cin >> respuesta;
            if (respuesta == 'N' || respuesta == 'n') {
              cout << "\n=========================================================================";
              cout << "\n\nTotal de la venta: $" << total << endl;
            Venta_Producto << setfill('-') << setw(60) << "" << setfill(' ') << endl;
            Venta_Producto << "Total:                                       $" << total
                         << endl;
            Venta_Producto << "Total (12% IVA):                                       $" << total2
                         << endl;
            }


          break;
        }

      }
          if (!encontrado) {
            cout << "\nNo se encontro un producto con el codigo \"" << auxcodigo << "\"" << endl;
            system("pause");
            system("cls");
            mostrarMenu();
          }


  }while((respuesta == 'S' || respuesta == 's') && !encontrado);

  Venta_Producto.close();
  system("pause");
  system("cls");
  cin.ignore();

  string encabezado;
    string num_factura;
    string num_orden;
    int op;
    encabezado_factura(encabezado);

    do{
        cout<<endl<<"========================================================================="<<endl;
        cout<<"1.- Factura"<<endl<<"2.- Consumidor final"<<endl<<">> ";cin>>op;
        cout<<endl<<"========================================================================="<<endl;
    }while(op<1||op>2);
    system("cls");

    //fflush(stdin);

    ///Ingreso de datos Factura o Consumidor Final
    string identificacion = facturacion(num_factura, encabezado, op, num_orden);

    cout<<"Desea cancelar su orden? (S/N): ";cin>>conf;

    if(conf=='N'||conf=='n'){
        Resta_Inventario(pila, n,cantidad);
        cout<<endl<<"========================================================================="<<endl;
        cout<<"GRACIAS POR SU COMPRA!!";
        cout<<endl<<"========================================================================="<<endl;
    }else{
        Cancelacion_Orden(identificacion, op);
    }
    fflush(stdin);
}

void Ingreso_Descripcion(){
    int cant_item, j, selec_item, it;
    char op;
    string aux_item;


    do{
        system("pause");
        system("cls");
        cout<<endl<<"========================================================================="<<endl;
        cout<<"   \t\t********  INGRESO ITEMS  ********    "<<endl;
        cout<<endl<<"========================================================================="<<endl;
        cout<<"Seleccione el item que desea agregar al producto: "<<endl;
        cout<<endl<<"========================================================================="<<endl;
        for(int k=0;k<14;k++){
            cout<<k+1<<".- "<<Items_total.Nom_Item[k]<<endl;
        }
        cout<<"========================================================================="<<endl;
        cout<<">>";cin>>it;
        cout<<"\nIngrese la cantidad de "<<Items_total.Nom_Item[it-1]<<": ";cin>>cant_item;
        Aux_Item.Item[it-1]=cant_item;

        cout<<"\nAgregar otro item? (S/N): ";cin>>op;

    }while(op=='s'||op=='S');
        cout<<endl;

    cout<<"Desea corregir la cantidad de algun item del producto? (S/N): ";cin>>op;

    while(op=='s'||op=='S'){

        system("pause");
        system("cls");
        cout<<endl<<"========================================================================="<<endl;
        cout<<"Escoja el item que desea modificar: "<<endl;
        cout<<endl<<"========================================================================="<<endl;

        for(j=0;j<14;j++){
            cout<<j+1<<".- "<<Items_total.Nom_Item[j]<<endl;
        }
        cout<<"========================================================================="<<endl;
        cout<<">>";cin>>selec_item;cout<<endl;

        cout<<"Ingrese la cantidad de "<<Items_total.Nom_Item[selec_item-1]<<": ";cin>>cant_item;
        Aux_Item.Item[selec_item-1]=cant_item;
        cout<<"\nDesea modificar otro item? "<<" (S/N): ";cin>>op;
    }

    ofstream archivo_descripcion_items;
    archivo_descripcion_items.open("Descripcion_inventario.txt",ios::app);
    for(j=0;j<14;j++){
        if(j!=13){
            aux_item=Convert(Aux_Item.Item[j]);
            archivo_descripcion_items<<aux_item+',';
        }else{
            aux_item=Convert(Aux_Item.Item[j]);
            archivo_descripcion_items<<aux_item+"\n";
        }
    }
    archivo_descripcion_items.close();
}

void agregarProducto() {

  int indice = Cont_Inventario();
  fflush(stdin);
  cout<<"========================================================================="<<endl;
    cout << "Ingrese codigo del producto: ";
  getline (cin, productos[indice].codigo);
  cout<<"========================================================================="<<endl;
  cout<< "\nNOTA: El NOMBRE debe estar en formato XXX-XXX (sin espacios)." << endl;
  cout<<"\n========================================================================="<<endl;
  cout << "Ingrese nombre del producto: ";
  getline (cin,  productos[indice].nombre);
  cout<<"========================================================================="<<endl;
  cout << "Precio: ";
  cin >> productos[indice].precio;

  Ingreso_Descripcion();

  ofstream archivo("menuproductos.txt", ios::app);

  if (archivo.is_open()) {
        archivo <<endl<<left  << productos[indice].codigo << "     "
        << productos[indice].nombre  << "          "
        << right << productos[indice].precio;

    archivo.close();

    cout << "Producto agregado exitosamente!" << endl;
  } else {
    cout << "Error al abrir el archivo menuproductos.txt" << endl;
  }
}



