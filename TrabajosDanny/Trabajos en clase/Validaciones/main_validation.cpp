#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "Validation.cpp"

using namespace std;

int main(){

    Validation<int> validaciones = Validation<int>();
    int nu = validaciones.enter_a_number("int");
    cout<< nu+1<<endl;
    fflush(stdin);
    Validation<string> validaciones2 = Validation<string>();
    string palabra = validaciones2.enter_a_char_or_string("string");
    cout<<palabra<<endl;
    return 0;
}