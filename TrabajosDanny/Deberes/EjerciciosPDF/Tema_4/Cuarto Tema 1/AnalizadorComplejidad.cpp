#include "AnalizadorComplejidad.h"
#include <iostream>
#include <cmath>

AnalizadorComplejidad::AnalizadorComplejidad(double valor) : n(valor) {}

double AnalizadorComplejidad::f1(double n) const { 
    return pow(log(n), 2); 
}

double AnalizadorComplejidad::f2(double n) const { 
    return 5 * log(n); 
}

double AnalizadorComplejidad::f3(double n) const { 
    return 10 * n; 
}

double AnalizadorComplejidad::f4(double n) const { 
    return n * log10(n); 
}

double AnalizadorComplejidad::f5(double n) const { 
    return pow(n, 1.5); 
}

double AnalizadorComplejidad::f6(double n) const { 
    return pow(n, 2); 
}

double AnalizadorComplejidad::f7(double n) const { 
    return pow(n, 2) * log(n); 
}

void AnalizadorComplejidad::analizarComplejidad() {
    std::cout << "Comparando crecimiento de funciones para n = " << n << ":\n";
    std::cout << "log(n)^2 = " << f1(n) << "\n";
    std::cout << "5 log(n) = " << f2(n) << "\n";
    std::cout << "10n = " << f3(n) << "\n";
    std::cout << "n log10(n) = " << f4(n) << "\n";
    std::cout << "n^(1+a) con a=0.5 = " << f5(n) << "\n";
    std::cout << "n^2 = " << f6(n) << "\n";
    std::cout << "n^2 log(n) = " << f7(n) << "\n";

    std::cout << "\nOrden de crecimiento de menor a mayor:\n";
    std::cout << "log(n)^2 < 5 log(n) < 10n < n log10(n) < n^(1+a) < n^2 < n^2 log(n)\n";
}