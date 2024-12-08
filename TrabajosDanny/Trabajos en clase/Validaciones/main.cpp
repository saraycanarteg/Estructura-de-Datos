#include<iostream>
#include <string>
#include"Validation.cpp"

using namespace std;

int main(){
    Validation<char*> validation_char;
    Validation<string> validation_string;
    Validation<int> validation_int;
    Validation<float> validation_float;
    char nombre[12];
    string apellido = validation_string.enter_a_char_or_string(12);
    strcpy(nombre, apellido.c_str());
    
    cout<<nombre;
}