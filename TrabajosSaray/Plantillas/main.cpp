#include "Calculo.cpp"
#include <stdio.h>
using namespace std;

int main (){
    float a,b; //declaración de variables
    printf("Calculadora para numeros mayores a cero\n\n");

        do{
            //ingreso de valores por teclado
            printf("Ingrese un numero a: ");
            scanf  ("%f", &a);
            
            printf("Ingrese un numero b: ");
            scanf  ("%f", &b);
                //estructura de control (imprime el mensaje y vuelve a pedir los datos)
                if (a<= 0 || b<=0 ){
                    printf("El numero ingresado no es valido. Ingrese un numero mayor a cero\n\n0");

                }

        }while ( a<= 0 || b<=0 );

    Calculo <float> intCalculo (a,b); //se crea el objeto clase Calculo y tipo float

    //asignacion de resultados de operaciones a variables
    float resultadoSuma = intCalculo.sumar();
    float resultadoResta = intCalculo.restar();
    float resultadoMultiplicacion = intCalculo.multiplicar();

    printf("La suma es: %f\n", resultadoSuma);
    printf("La resta es: %f\n", resultadoResta);
    printf("La multiplicacion es: %f\n", resultadoMultiplicacion);

    return 0;
}