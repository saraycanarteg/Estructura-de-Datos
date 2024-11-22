#include <iostream>
#include <conio.h>
using namespace std;

template <typename T> //declaracion de la plantilla clase Calculo
class Calculo {
    public:
        Calculo (T a, T b): a(a), b(b){}; //constructor inicializa 2 variables privadas
        
        //funciones
        T sumar ();
        T restar ();
        T multiplicar ();

    private:
        //atributos (almacenan valores tipo T usado para operaciones)
        T a;
        T b;   

};
