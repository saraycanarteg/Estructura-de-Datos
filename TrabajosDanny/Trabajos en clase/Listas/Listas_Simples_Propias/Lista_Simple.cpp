/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Danny Ayuquina                                      *
 * Fecha de creacion:              28/11/2024                                          *
 * Fecha de modificacion:          28/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#include "Lista_Simple.h"

using namespace std;

template <typename T>
Lista_Simple<T>::Lista_Simple(){
    cabeza = NULL;
}

template <typename T>
Nodo<T>* Lista_Simple<T>::get_Cabeza(){
    return cabeza;
}


template <typename T>
void Lista_Simple<T>::insertar_cabeza(T _dato){

    Nodo<T>* nuevo = new Nodo<T>(_dato);

    if(cabeza == NULL){
        cabeza = nuevo;
    }else{
        Nodo<T>* aux = cabeza;

        while(aux->get_Siguiente() != NULL){
            aux = aux->get_Siguiente();
        }

        aux->set_Siguiente(nuevo);
    }
}

template <typename T>
bool Lista_Simple<T>::buscar(T _dato){

    Nodo<T>* aux = cabeza;
    while(aux != NULL){
        if(aux->get_Dato() == _dato){
            return true;
        }
        aux = aux->get_Siguiente();
    }

    return false;
}

template <typename T>
bool Lista_Simple<T>::eliminar(T _dato){

    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;

    while (aux != NULL){
        if(aux->get_Dato()==_dato){
            if(anterior == NULL){
                cabeza = aux->get_Siguiente();
            }else{
                anterior->set_Siguiente(aux->get_Siguiente());
            }
            delete aux;
            return true;
        }
        anterior = aux;
        aux = aux->get_Siguiente();
    }

    return false;
}

template <typename T>
void Lista_Simple<T>::mostrar(){

    Nodo<T>* aux = cabeza;

    while(aux != NULL){
        cout << aux->get_Dato() << " --> ";
        aux = aux->get_Siguiente(); 
    }

    cout << "NULL" << endl;
}