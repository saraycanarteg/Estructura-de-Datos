#include<iostream>
#include<conio.h>
#include<stdio.h>

/////// de cola ///

int sumaCola(int n, int acumulado = 0) {
    if (n == 0) return acumulado;
    return sumaCola(n - 1, acumulado + n);
}

/////// mutua ///

bool esPar(int n);
bool esImpar(int n);

bool esPar(int n) {
    if (n == 0) return true;
    return esImpar(n - 1);
}

bool esImpar(int n) {
    if (n == 0) return false;
    return esPar(n - 1);
}

/////// simple ///
int factorialSimple(int n) {
    if (n <= 1) return 1;
    return n * factorialSimple(n - 1);
}

/////// no cola ///
int sumaNoCola(int n) {
    if (n == 0) return 0;
    return n + sumaNoCola(n - 1); // La suma se hace después de la llamada recursiva
}

/////// anidada ///
int fibonacciAnidada(int n) {
    if (n <= 1) return n;
    return fibonacciAnidada(n - 1) + fibonacciAnidada(n - 2);
}

/////// múltiple ///
int sumaMultiple(int n) {
    if (n <= 1) return n;
    return sumaMultiple(n / 2) + sumaMultiple(n / 2);
}

/////// indirecta ///
void funcionA(int n);
void funcionB(int n);

void funcionA(int n) {
    if (n > 0) {
        std::cout << "A: " << n << std::endl;
        funcionB(n - 1);
    }
}

void funcionB(int n) {
    if (n > 0) {
        std::cout << "B: " << n << std::endl;
        funcionA(n - 1);
    }
}


