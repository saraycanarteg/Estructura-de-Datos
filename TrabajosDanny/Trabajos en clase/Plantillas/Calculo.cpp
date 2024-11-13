#include<iostream>
#include<conio.h>
#include <stdio.h>

#include "Calculo.h"

using namespace std;

template <typename T>
T Calculo<T>::sumar(){
    return a + b;
}

template <typename T>
T Calculo<T>::restar() { 
    return a - b;
}

template <typename T>
T Calculo<T>::multiplicar() {
    return a * b;
}