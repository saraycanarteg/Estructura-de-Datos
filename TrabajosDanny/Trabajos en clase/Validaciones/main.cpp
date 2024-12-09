#include<iostream>
#include <string>
#include"Validation.cpp"

using namespace std;

int main(){
    Validation<char*> validation_char;
    Validation<string> validation_string;
    Validation<int> validation_int;
    Validation<float> validation_float;
    char nombres_char[20], apellidos_char[20];
    cout<<"Nombres:";
    string nombres = validation_string.enter_a_char_or_string_with_may(20);
    strcpy(nombres_char, nombres.c_str());
    cout<<endl<<"Apellidos: ";
    string apellidos = validation_string.enter_a_char_or_string_with_may(20);
    strcpy(apellidos_char, apellidos.c_str());
    cout<<endl;
    
    cout<<nombres_char<<"----"<<apellidos_char;
}