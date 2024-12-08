/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Danny Ayuquina                                      *
 * Fecha de creacion:              28/11/2024                                          *
 * Fecha de modificacion:          28/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#include "Nodo.h"

using namespace std;

//CONSTRUCTOR
template <typename T>
Nodo<T>::Nodo(T _dato){
    dato = _dato;
    siguiente = NULL;
}

//Aquí no añadí el inline
template <typename T>
void Nodo<T>::set_Dato(T _dato){
    dato = _dato;
}

template <typename T>
T Nodo<T>::get_Dato(){
    return dato;
}

template <typename T>
void Nodo<T>::set_Siguiente(Nodo* _siguiente){
    siguiente = _siguiente;
}

template <typename T>
Nodo<T>* Nodo<T>::get_Siguiente(){
    return siguiente;
}
