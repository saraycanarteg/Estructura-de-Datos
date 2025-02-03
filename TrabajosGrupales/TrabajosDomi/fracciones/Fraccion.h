#ifndef FRACCION_H
#define FRACCION_H

#include <iostream>

int gcd(int a, int b) {
     while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Fraccion {
private:
    int numerador;
    int denominador;

public:
    // Constructor
    Fraccion(int num = 0, int denom = 1) : numerador(num), denominador(denom) {
        simplificar();
    }

    // Función para ingresar una fracción
    void ingresarFraccion() {
        std::cout << "Ingrese el numerador: ";
        std::cin >> numerador;
        do {
            std::cout << "Ingrese el denominador (diferente de 0): ";
            std::cin >> denominador;
        } while (denominador == 0);
        simplificar();
    }

    // Función para simplificar la fracción
    void simplificar() {
        int divisor = gcd(numerador, denominador);
        numerador /= divisor;
        denominador /= divisor;
    }

    // Operador para sumar fracciones
    Fraccion operator+(const Fraccion& otra) const {
        int nuevoNumerador = numerador * otra.denominador + otra.numerador * denominador;
        int nuevoDenominador = denominador * otra.denominador;
        return Fraccion(nuevoNumerador, nuevoDenominador);
    }

    // Función para mostrar la fracción
    void mostrar() const {
        if (denominador == 1) {
            std::cout << numerador;
        } else {
            std::cout << numerador << "/" << denominador;
        }
    }
};

#endif // FRACCION_H