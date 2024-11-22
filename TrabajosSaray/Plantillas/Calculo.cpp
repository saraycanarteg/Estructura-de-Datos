#include <iostream>
#include <conio.h>
#include "Calculo.h"
#include <stdio.h>
using namespace std;

//declaracion de funciones template para +, - , *

template <typename T> //si no se pone esto marca error, es decir que si la clase es template los metodos tambien
T Calculo <T>:: sumar(){
    return a+b;
}

template <typename T>
T Calculo <T>:: restar(){
    return a-b;
}

template <typename T>
T Calculo <T>:: multiplicar(){
    return a*b;
}
