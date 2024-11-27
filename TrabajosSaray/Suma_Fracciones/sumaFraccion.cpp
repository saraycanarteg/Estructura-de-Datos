#include <iostream>
#include <conio.h>
#include "sumaFraccion.h"
#include <stdio.h>

using namespace std;

template <typename F>
F Fraccion <F>:: calculoDenominador(const Fraccion<F>& otraFraccion){
    return denominador * otraFraccion.denominador;
}


template <typename F>
F Fraccion <F>:: calculoNumerador(const Fraccion<F>& otraFraccion){
    F numTemporal1 = numerador * otraFraccion.denominador;
    F numTemporal2 = otraFraccion.numerador * denominador;

    return  numTemporal1 + numTemporal2; 
}

template <typename F>
string Fraccion <F>:: sumar(const Fraccion<F>& otraFraccion){
    F newNumerador = calculoNumerador (otraFraccion);
    F newDenominador = calculoDenominador (otraFraccion);
    return "La suma de la fraccion es: " + to_string(newNumerador) + "/" + to_string(newDenominador);
}