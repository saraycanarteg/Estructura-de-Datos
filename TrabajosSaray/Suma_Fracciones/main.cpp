#include "sumaFraccion.cpp"
#include <iostream>
#include <limits> 
using namespace std;


void ingresarEntero(const string& mensaje, int& valor, bool noCero = false) {
    bool entradaValida = false;
    while (!entradaValida) {
        cout << mensaje;
        cin >> valor;
        
        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, ingrese un numero entero.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (noCero && valor == 0) {
            cout << "El valor no puede ser cero.\n";
        } else {
            entradaValida = true;
        }
    }
}

int main() {
    int num1, denom1, num2, denom2;

    ingresarEntero("Ingrese el numerador de la Fraccion 1: ", num1);
    ingresarEntero("Ingrese el denominador de la Fraccion 1 (no puede ser 0): ", denom1, true);

    ingresarEntero("Ingrese el numerador de la Fraccion 2: ", num2);
    ingresarEntero("Ingrese el denominador de la Fraccion 2 (no puede ser 0): ", denom2, true);

    Fraccion<int> fraccion1(num1, denom1);
    Fraccion<int> fraccion2(num2, denom2);

    cout << "La suma de las fracciones es: " << fraccion1.sumar(fraccion2) << endl;

    return 0;
}
