#ifndef INGRESO_H
#define INGRESO_H

#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

// Clase plantilla para ingresar datos
template <typename T>
class Ingreso {
public:
    T ingresar(const char* msj);
};

// Especialización para ingresar enteros
template <>
int Ingreso<int>::ingresar(const char* msj) {
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    cout << msj;
    while ((c = getch()) != 13) {
        if (c >= '0' && c <= '9') {
            cout << c;
            cad[i++] = c;
        } else if (c == 8 && i > 0) {
            cout << "\b \b";
            i--;
        }
    }
    cad[i] = '\0';
    valor = atoi(cad);
    return valor;
}

// Especialización para ingresar flotantes
template <>
float Ingreso<float>::ingresar(const char* msj) {
    char cad[10];
    char c;
    int i = 0;
    float valor = 0;
    bool puntoDecimal = false;
    cout << msj;
    while ((c = getch()) != 13) {
        if ((c >= '0' && c <= '9') || (c == '.' && !puntoDecimal)) {
            if (c == '.') puntoDecimal = true;
            cout << c;
            cad[i++] = c;
        } else if (c == 8 && i > 0) {
            if (cad[i - 1] == '.') puntoDecimal = false;
            cout << "\b \b";
            i--;
        }
    }
    cad[i] = '\0';
    valor = atof(cad);
    return valor;
}

// Especialización para ingresar caracteres
template <>
char Ingreso<char>::ingresar(const char* msj) {
    char c;
    cout << msj;
    while (true) {
        c = getch();
        if (isalpha(c)) {
            cout << c;
            return c;
        } else if (c == 8) {
            cout << "\b \b";
        }
    }
}

// Especialización para ingresar strings
template <>
string Ingreso<string>::ingresar(const char* msj) {
    char cad[10];
    char c;
    int i = 0;
    string valor;
    cout << msj;
    while ((c = getch()) != 13) {
        if (isalpha(c)) {
            cout << c;
            cad[i++] = c;
        } else if (c == 8 && i > 0) {
            cout << "\b \b";
            i--;
        }
    }
    cad[i] = '\0';
    valor = cad;
    return valor;
}

// Especialización para ingresar doubles
template <>
double Ingreso<double>::ingresar(const char* msj) {
    char cad[20];
    char c;
    int i = 0;
    double valor = 0;
    bool puntoDecimal = false;
    cout << msj;
    while ((c = getch()) != 13) {
        if ((c >= '0' && c <= '9') || (c == '.' && !puntoDecimal)) {
            if (c == '.') puntoDecimal = true;
            cout << c;
            cad[i++] = c;
        } else if (c == 8 && i > 0) {
            if (cad[i - 1] == '.') puntoDecimal = false;
            cout << "\b \b";
            i--;
        }
    }
    cad[i] = '\0';
    valor = atof(cad);
    return valor;
}

#endif // INGRESO_H
