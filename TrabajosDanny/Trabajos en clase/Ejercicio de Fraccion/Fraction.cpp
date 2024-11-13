#include<iostream>
#include<conio.h>
#include <stdio.h>

#include "Fraction.h"

using namespace std;


template <typename T>
T Fraction<T>::get_denominator(){
    return denominator;
}

template <typename T>
T Fraction<T>::get_numerator(){
    return numerator;
}

template <typename T>
void Fraction<T>:: set_numerator(T new_numerator){
    numerator = new_numerator;
}

template <typename T>
void Fraction<T>:: set_denominator(T new_denominator){
    denominator = new_denominator; 
}

template <typename T>
void Fraction<T>::adition(Fraction &result_fraction, Fraction fraction_1, Fraction fraction_2){
    T mcm = least_common_multiple(fraction_1.denominator, fraction_2.denominator);

    if(mcm != 0){
        if(fraction_1.denominator < fraction_2.denominator){
            result_fraction.denominator = fraction_2.denominator;
            result_fraction.numerator = fraction_2.numerator + (fraction_1.numerator*mcm);
        }else{
            result_fraction.denominator = fraction_1.denominator;
            result_fraction.numerator = fraction_1.numerator + (fraction_2.numerator*mcm);
            
        }
    }else{
        result_fraction.denominator = fraction_1.denominator*fraction_2.denominator;
        result_fraction.numerator = (fraction_1.numerator*fraction_2.denominator)+(fraction_1.denominator*fraction_2.numerator);
    }
   
}

template <typename T>
T Fraction<T>::least_common_multiple(T denominator_1, T denominator_2){
    T mcm = 0;

    if((denominator_1 % denominator_2) == 0){
        mcm = denominator_1/denominator_2;
    }else if((denominator_2 % denominator_1) == 0){
        mcm = denominator_2/denominator_1;
    }

    return mcm;
}

