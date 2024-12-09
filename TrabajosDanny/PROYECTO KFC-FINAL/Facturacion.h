#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include<string.h>
#include<stdlib.h>

#include<string.h>
#include "fecha.h"
#include"V_caracteres.h"

using namespace std;

int cont_facturas=0, cont_orden=0, i;

///Declaración estructuras
struct Facturas{
    string tipo_identificacion[4]={"##########", "RUC", "Cedula"};
    char identificacion[11]="##########";
    char cliente[50]="CONSUMIDOR FINAL";
    char telefono[11]="##########";;
    string direccion="##########";;
    char correo[20]="##########";;
}Datos, Consumidor_final;

///Funciones
void encabezado_factura(string &encabezado){
    ifstream factura;
    string linea;
    factura.open("Encabezado facturas.txt", ios::in);

    while(!factura.eof()){
        getline(factura, linea);
        encabezado=encabezado+linea+'\n';
    }
    factura.close();
}

int numero_factura(){
    string aux;
    int aux1;
    ifstream N_Factura;
    N_Factura.open("N_Factura.txt", ios::in);
    if(N_Factura.fail()){
        cout<<"Nel"<<endl;
    }
    getline(N_Factura, aux);
    aux1 = stoi(aux);
    return aux1;

}

bool Validacion_Cedula(int tamanio, string cedula){

    int j, dig_impar=0, dig_par=0, suma_impares=0, suma_pares=0, comp, comp2;
    string dig1, dig2;

    for(j=0;j<tamanio-1;j++){
        if((j+1)%2!=0){
            dig1=cedula[j];
            dig_impar=2*stoi(dig1);
            if(dig_impar>9){
                dig_impar=dig_impar-9;
            }
            suma_impares+=dig_impar;
        }else{
            dig2=cedula[j];
            dig_par=stoi(dig2);
            suma_pares+=dig_par;
        }
    }

    dig1=cedula[9];
    dig_par=stoi(dig1);
    comp = (suma_impares+suma_pares)%10;
    comp2=10-comp;
    if(comp==0){
        if(comp==dig_par){
            return 1;
        }
    }else if(comp2==dig_par){
            return 1;
    }else{
        return 0;
    }

}

string facturacion(string num_factura, string encabezado, int op, string num_orden){
    //VARIABLES
    int pos_identificacion, tamanio;
    bool validacion, validacion2;
    string fecha=imprimirfecha();

    ///Recuperacion del numero de la factura
    cont_facturas=numero_factura();

    ///Creación de archivo txt
    ofstream factura;
    cont_orden++;
    num_orden=to_string(cont_orden);


    cont_facturas++;
    num_factura = to_string(cont_facturas);

    ///Entrada de datos
    if(op==1){
        ///Identificación
        do{
            cout<<"--------------SISTEMA DE FACTURACION---------------"<< endl;
            cout<<"TIPO DE IDENTIFICACION: "<<endl;
            for(i=1;i<3;i++){
                cout<<i<<".- "<<Datos.tipo_identificacion[i]<<endl;
            }
            cout<<">> ";cin>>pos_identificacion;

            if(pos_identificacion!=1&&pos_identificacion!=2){
                cout<<"Opcion invalida. Intente de nuevo..."<<endl<<endl;
                system("pause");
                system("cls");
            }
        }while(pos_identificacion!=1&&pos_identificacion!=2);
        cin.ignore();

        ///Número de identificación
         do{
            cout<<"Identificacion: ";gets(Datos.identificacion);
            tamanio=strlen(Datos.identificacion);
            validacion=v_numeros(tamanio,Datos.identificacion);

            if((tamanio!=10||validacion==0)&&(pos_identificacion==2)){
                cout<<"Identificacion mal ingresada. Intente de nuevo..."<<endl;
                system("pause");
                tamanio=0;
                cout<<endl;
            }else if((tamanio!=13||validacion==0)&&pos_identificacion==1){
                cout<<"Identificacion mal ingresada. Intente de nuevo..."<<endl;
                system("pause");
                cout<<endl;
                tamanio=0;
            }

            string cedula=Datos.identificacion;

            if(pos_identificacion==2&&tamanio==10&&validacion){
                validacion2=Validacion_Cedula(tamanio, cedula);
            }else if(pos_identificacion==1&&tamanio==13&&validacion){
                validacion2=Validacion_Cedula(tamanio-3, cedula);
                if(validacion2==true){
                    if(cedula[10]!='0'||cedula[11]!='0'||cedula[12]!='1'){
                        validacion2=false;
                    }
                }
            }
            if(!validacion2){
                cout<<"La identificacion ingresada no existe. Intente de nuevo..."<<endl;
                system("pause");
                cout<<endl;
            }

        }while(tamanio==0||validacion==0||validacion2==0);

        ///Almacenamiento de facturas (dirección carpeta de facturas)
        factura.open("E:\\FDP\\PROYECTO KFC-FINAL\\Facturas\\"+string(Datos.identificacion)+".txt",ios::out);


        //Detección de error al abrir archivo
        if(factura.fail()){
            cout<<"No se ha podido crear la factura..."<<endl;
            exit(1);
        }

        factura<<encabezado+fecha+"\n";

        factura<<"Tipo de identificacion: "+Datos.tipo_identificacion[pos_identificacion]+'\n';
        factura<<"Identificacion: "+string(Datos.identificacion)+'\n';

        ///Nombre del cliente
        do{
            cout<<"Nombre: ";gets(Datos.cliente);
            tamanio=strlen(Datos.cliente);
            validacion=v_letras(tamanio,Datos.cliente);

            if(validacion==0){
                cout<<"Nombre mal ingresado. Intente de nuevo..."<<endl;
                system("pause");
                cout<<endl;
            }

        }while(validacion==0);
        factura<<"Cliente: "+string(Datos.cliente)+'\n';

        ///Número de teléfono
        do{
            cout<<"Telefono: ";gets(Datos.telefono);
            tamanio=strlen(Datos.telefono);
            validacion=v_numeros(tamanio,Datos.telefono);

            if(tamanio!=10||validacion==0){
                cout<<"Telefono mal ingresado. Intente de nuevo..."<<endl;
                system("pause");
                cout<<endl;
            }

        }while(tamanio!=10||validacion==0);
        factura<<"Telefono: "+string(Datos.telefono)+'\n';

        ///Dirección
        cout<<"Direccion: ";getline(cin,Datos.direccion);
        factura<<"Direccion: "+Datos.direccion+'\n';

        ///Correo
        validacion=false;
        do{
            cout<<"Correo: ";gets(Datos.correo);
            tamanio=strlen(Datos.correo);
            for(i=0;i<tamanio;i++){
                if(Datos.correo[i]=='@'){
                    validacion=1;
                    break;
                }
            }
            if(validacion==0){
                cout<<"Correo mal ingresado. Intente de nuevo..."<<endl;
                validacion=0;
                system("pause");
            }
        }while(validacion==0);

        factura<<"Correo: "+string(Datos.correo)+'\n'+'\n';
    }else{
        ///Enumeración Consumidor Final(dirección de carpeta consumidor final)
        factura.open("E:\\FDP\\PROYECTO KFC-FINAL\\Consumidor final\\"+string(num_factura)+".txt",ios::out);

        factura<<encabezado+fecha+"\n";
        factura<<"Tipo de identificacion: "+Consumidor_final.tipo_identificacion[0]+'\n';
        factura<<"Identificacion: "+string(Consumidor_final.identificacion)+'\n';
        factura<<"Cliente: "+string(Consumidor_final.cliente)+'\n';
        factura<<"Telefono: "+string(Consumidor_final.telefono)+'\n';
        factura<<"Direccion: "+Consumidor_final.direccion+'\n';
        factura<<"Correo: "+string(Consumidor_final.correo)+'\n';
    }
    factura<<"------------------------------------------------------------";
    factura<<'\n';

    factura<<"                  ORDEN: #"+num_orden+'\n';
    factura<<"Factura #011-032-0"+num_factura+'\n';

    ///Guardado de numero de factura
    ofstream N_Factura;
    N_Factura.open("N_Factura.txt", ios::out);
    N_Factura<<num_factura;
    N_Factura.close();

    ///Productos
    ifstream Fact_Prod;
    Fact_Prod.open("Venta_Producto.txt", ios::in);
    string texto="", linea;
    while(!Fact_Prod.eof()){
        getline(Fact_Prod, linea);
        texto=texto+linea+"\n";
    }

    factura<<texto+"\n";
    //Cierre archivo factura
    factura.close();

    return Datos.identificacion;
}

///Búsqueda de facturas
void Busqueda_Facturas(){
    string linea;
    int pos_identificacion, tamanio, op;
    bool validacion, validacion2;
    char ident[20];

        cout<<endl<<"========================================================================="<<endl;
    cout<<"   \t********  BUSQUEDA DE FACTURAS  ********    "<<endl;
    cout<<"========================================================================="<<endl;
    cout<<"1. Facturas\n2. Consumidor Final\n>>";cin>>op;
    cin.ignore();

    if(op==1){
        do{
                cout<<"\nTIPO DE IDENTIFICACION: "<<endl;
                for(i=1;i<3;i++){
                    cout<<i<<".- "<<Datos.tipo_identificacion[i]<<endl;
                }
                cout<<">> ";cin>>pos_identificacion;

                if(pos_identificacion!=1&&pos_identificacion!=2){
                    cout<<"Opcion invalida. Intente de nuevo..."<<endl<<endl;
                    system("pause");
                    system("cls");
                }
            }while(pos_identificacion!=1&&pos_identificacion!=2);
            cin.ignore();

        do{
                cout<<"Identificacion: ";gets(ident);
                tamanio=strlen(ident);
                validacion=v_numeros(tamanio,ident);

                string cedula = ident;

                if(pos_identificacion==2&&tamanio==10&&validacion ){
                    validacion2=Validacion_Cedula(tamanio, cedula);
                }else if(pos_identificacion==1&&tamanio==13&&validacion){
                    validacion2=Validacion_Cedula(tamanio-3, cedula);
                    if(validacion2==true){
                        if(cedula[10]!='0'||cedula[11]!='0'||cedula[12]!='1'){
                            validacion2=false;
                        }
                    }
                }
                if(!validacion2){
                    cout<<"La identificacion ingresada no existe. Intente de nuevo..."<<endl;
                    system("pause");
                    cout<<endl;
                }

            }while(tamanio==0||validacion==0||validacion2==0);
        system("cls");
        ifstream bfact;
        bfact.open("E:\\FDP\\PROYECTO KFC-FINAL\\Facturas\\"+string(ident)+".txt", ios::in);

        if(bfact.fail()){
            cout<<"No se ha encontrado una factura con numero de identificacion: "<<ident<<endl;
        }else{
            while(!bfact.eof()){
                getline(bfact, linea);
                cout<<linea<<endl;
            }
        }

    }else{
        string num_cf;
        cout<<"\nIngrese el numero de factura: "<<endl<<">>";getline(cin, num_cf);
        system("cls");
        ifstream bcf;
        bcf.open("E:\\FDP\\PROYECTO KFC-FINAL\\Consumidor final\\"+num_cf+".txt", ios::in);

        if(bcf.fail()){
            cout<<"No se ha encontrado una factura con esa ennumeracion"<<endl;
        }else{
            while(!bcf.eof()){
                getline(bcf, linea);
                cout<<linea<<endl;
            }
        }

    }
    system("pause");
    system("cls");
}
