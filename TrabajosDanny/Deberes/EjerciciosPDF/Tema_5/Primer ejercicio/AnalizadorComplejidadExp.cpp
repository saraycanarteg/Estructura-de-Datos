#include "AnalizadorComplejidadExp.h"
#include <iostream>
#include <cmath>

AnalizadorComplejidadExp::AnalizadorComplejidadExp(int valor) : n(valor) {}

bool AnalizadorComplejidadExp::perteneceOGrande1(int n) const {
    return (pow(2, n + 1) <= 2 * pow(2, n));
}

bool AnalizadorComplejidadExp::perteneceOGrande2(int n) const {
    return (pow(2, 2 * n) <= pow(2, n));
}

void AnalizadorComplejidadExp::analizarComplejidad() const {
    std::cout << "Analizando 2^(n+1) existe O(2^n)... ";
    if (perteneceOGrande1(n)) {
        std::cout << "Verdadero \n";
    } else {
        std::cout << "Falso \n";
    }

    std::cout << "Analizando 2^(2n) no existe O(2^n)... ";
    if (!perteneceOGrande2(n)) {
        std::cout << "Verdadero \n";
    } else {
        std::cout << "Falso \n";
    }
}