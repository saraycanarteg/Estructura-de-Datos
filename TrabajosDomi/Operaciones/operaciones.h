#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <iostream>
using namespace std;

void suma() {
    double a, b;
    cout << "Ingrese dos números para sumar: ";
    cin >> a >> b;
    cout << "Resultado: " << (a + b) << endl;
}

void resta() {
    double a, b;
    cout << "Ingrese dos números para restar: ";
    cin >> a >> b;
    cout << "Resultado: " << (a - b) << endl;
}

void multiplicacion() {
    double a, b;
    cout << "Ingrese dos números para multiplicar: ";
    cin >> a >> b;
    cout << "Resultado: " << (a * b) << endl;
}

#endif // OPERACIONES_H