/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Danny Ayuquina                                      *
 * Fecha de creacion:              28/11/2024                                          *
 * Fecha de modificacion:          28/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/

#pragma once
#include "Nodo.h"

using namespace std;

template <typename T>
class Lista_Simple {
    
    private:

        Nodo<T>* cabeza;

    public:

        Lista_Simple();

        void insertar_cabeza(T);
        Nodo<T>* get_Cabeza();
        bool buscar(T);
        bool eliminar(T);
        void mostrar();

};

