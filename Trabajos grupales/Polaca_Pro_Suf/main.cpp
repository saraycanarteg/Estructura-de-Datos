#include <iostream>
#include <conio.h> // Para getch()
#include "CalculadoraPolaca.cpp"

using namespace std;

int main() {
    string infijoExpresion;
    char tecla;
    char ultimaTecla = '\0'; // Almacena el último carácter ingresado

    do{
        cout<<"CONVERSOR DE EXPERSIONES MATEMATICAS A POLACAS"<<endl<<endl;
        cout << "Ingrese una expresion (solo se permiten numeros y operadores matematicos):";

        while (true) {
            tecla = getch(); // Captura una tecla sin mostrarla en consola

            if (tecla == '\r') { // Enter para finalizar la entrada
                cout << endl;
                break;
            } else if (tecla == '\b') { // Retroceso
                if (!infijoExpresion.empty()) {
                    infijoExpresion.pop_back();
                    ultimaTecla = infijoExpresion.empty() ? '\0' : infijoExpresion.back();
                    cout << "\b \b"; // Borra el último carácter en consola
                }
            } else if (isdigit(tecla) || tecla == '(' || tecla == ')') {
                infijoExpresion += tecla;
                ultimaTecla = tecla;
                cout << tecla; // Imprime caracteres válidos
            } else if (Calculadora::esOperador(tecla) && !Calculadora::esOperador(ultimaTecla)) {
                infijoExpresion += tecla;
                ultimaTecla = tecla;
                cout << tecla; // Imprime el operador si el último carácter no es otro operador
            }
        }
        if (!Calculadora::esExpresionValida(infijoExpresion)) {
            cout << "\nExpresion invalida. Asegurese de usar al menos dos numeros con un operador y que los operadores no esten consecutivos.\n";
            system("pause");
            system("cls");
        }else{
            break;
        }

    }while(true);

    string posfijaExpresion = Calculadora::infijaAPosfija(infijoExpresion);
    string prefijaExpresion = Calculadora::infijaAPrefija(infijoExpresion);

    cout << "Expresion original: " << infijoExpresion << endl;
    cout << "Expresion postfija: " << posfijaExpresion << endl;
    cout << "Expresion prefija: " << prefijaExpresion << endl;

    return 0;
}
