#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;


struct Nodo{
    int dato;
    int cant;
    Nodo *siguiente;
};

void Agregar_Pila(Nodo *&pila, int n, int cant){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo -> dato = n;
    nuevo_nodo -> cant = cant;
    nuevo_nodo -> siguiente = pila;
    pila = nuevo_nodo;
    cout<<"Elemento "<< n << " ingresado correctamente."<<endl<<endl;
}

void Sacar_Pila(Nodo *&pila, int &n, int &cant){
    Nodo *aux = pila;
    n = aux->dato;
    cant = aux->cant;
    pila = aux->siguiente;
    delete aux;
}
