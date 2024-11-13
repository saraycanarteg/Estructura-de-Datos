#include<iostream>
#include<conio.h>
#include <stdio.h>

#include "Fraction.cpp"
#include "Keyboard_intro.cpp"

using namespace std;

int main(){
    cout<<"FRACCION 1 "<<endl;
    cout<<"Numerador: ";
    int numerator_1 = ingreso_por_teclado_int();
    
    cout<<"\nDenominador: ";
    int denominator_1 = ingreso_por_teclado_int();
    
    cout<<"\n\nFRACCION 2 "<<endl;
    cout<<"Numerador: ";
    int numerator_2 = ingreso_por_teclado_int();
    
    cout<<"\nDenominador: ";
    int denominator_2 = ingreso_por_teclado_int();


    Fraction<int> fraction_1(numerator_1,denominator_1), fraction_2(numerator_2,denominator_2);

    Fraction<int> result_fraction(0, 0);

    result_fraction.adition(result_fraction,fraction_1,fraction_2);

    if((result_fraction.get_numerator()/result_fraction.get_denominator())!= 1){
        cout<<"\n\nFRACCION RESULTANTE: "<<result_fraction.get_numerator()<<'/'<<result_fraction.get_denominator()<<endl;
    }else{
        cout<<"\n\nFRACCION RESULTANTE: "<<result_fraction.get_numerator()<<'/'<<result_fraction.get_denominator()<<" = 1"<<endl;

    }

    return 1;
}