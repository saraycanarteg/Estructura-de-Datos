#include <iostream>
#include <conio.h>
using namespace std;

template <typename F> //template tipo F clase Fraccion 
class Fraccion {
    public: 
        Fraccion(F numerador, F denominador):numerador(numerador), denominador(denominador){}; //constructor

        string sumar(const Fraccion<F>& otraFraccion); //declaracion metodo

    private:
    //variables 
        F numerador;
        F denominador;

        F calculoDenominador(const Fraccion<F>& otraFraccion);
        F calculoNumerador(const Fraccion<F>& otraFraccion);
};

