#include <iostream>
#include "Ingreso.h"
#include "Operaciones.cpp"
#include "Fraccion.h"

using namespace std;

int main() {
    Ingreso<int> ingresoInt;
    int numero1 = ingresoInt.ingresar("Ingrese un valor entero: ");
    cout << endl;
    int numero2 = ingresoInt.ingresar("Ingrese otro valor entero: ");
    cout << endl;
    int resultadoInt = sumar(numero1, numero2);
    cout << "Resultado entero: " << resultadoInt << endl;

    Ingreso<float> ingresoFloat;
    float num1 = ingresoFloat.ingresar("Ingrese un valor flotante: ");
    cout << endl;
    float num2 = ingresoFloat.ingresar("Ingrese otro valor flotante: ");
    cout << endl;
    float resultadoFloat = sumar(num1, num2);
    cout << "Resultado flotante: " << resultadoFloat << endl;

    Fraccion fraccion1, fraccion2;

    cout << "Ingrese la primera fraccion:" << endl;
    fraccion1.ingresarFraccion();
    cout << "\nIngrese la segunda fraccion:" << endl;
    fraccion2.ingresarFraccion();
    Fraccion resultado = fraccion1 + fraccion2;
    cout << "\nEl resultado de la suma es: ";
    resultado.mostrar();

    cout << endl;

    return 0;
}
