#include<iostream>
#include <conio.h>
#include <iostream>

using namespace std;

template <typename T>
class Calculo
{
public:
    Calculo(T a, T b) : a(a), b(b) {};

    T sumar ();

    T restar();

    T multiplicar();
private:
    T a;
    T b;
};