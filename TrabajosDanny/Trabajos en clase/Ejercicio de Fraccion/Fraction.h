#include<iostream>
#include <conio.h>
#include <iostream>

using namespace std;

template <typename T>
class Fraction
{
private:
    T numerator;
    T denominator;
public:
    
    Fraction(T numerator, T denominator) : numerator(numerator), denominator(denominator){};

    T get_numerator();

    T get_denominator();
    
    void set_numerator(T new_numerator);

    void set_denominator(T new_denominator);

    void adition(Fraction &result_fraction, Fraction fraction_1, Fraction fraction_2);

    T least_common_multiple(T denominator_1, T denominator_2);

};

