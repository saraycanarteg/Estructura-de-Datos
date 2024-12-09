#include <iostream>
#include <string.h>
#include "Validation.h"

using namespace std;

template <typename T>
Validation<T>::Validation(){}


// *******************INPUTS DE DATOS*********************
template <typename T>
T Validation<T>::enter_a_number(char *data_type){
    char cad[20], c;
    int i = 0;
    bool validation_decimal=false;

    while(((c = getch())!=13)){
        
        if (c>='0' && c <= '9' ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c == '.' && (validation_decimal==false) && !(strcmp(data_type, "float"))){
            printf("%c", c);
            cad[i++] = c;
            validation_decimal=true;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
            if(cad[i]=='.'){
                validation_decimal=false;
            }
        }
    }
    cad[i++]='\0';
    T return_data = data_convertion_to_number(cad, data_type);   
    return return_data;
}

template <typename T>
T Validation<T>::enter_a_char_or_string(int data_size){
    char cad[data_size], c;
    int i = 0;
     while(((c = getch())!=13)){
        if ((c>='a' && c <= 'z') || (c>='A'&&c<='Z') || (c==' ') ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }
    cad[i++]='\0';
    return cad;
}

template <typename T>
T Validation<T>::enter_a_char_or_string_only_nums(int data_size){
    char cad[data_size], c;
    int i = 0;
     while(((c = getch())!=13)){
        if ((c>='0' && c <= '9') ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }
    cad[i++]='\0';
    return cad;
}


template <typename T>
T Validation<T>::enter_a_char_or_string_with_may(int data_size){
    char cad[data_size], c;
    int i = 0;
    while(((c = getch())!=13)){
        if ((c>='a' && c <= 'z') || (c>='A'&&c<='Z') ){
            
            if(c>='a' && c <= 'z') {
                if((i == 0 || cad[i-1]==' ')){
                c = c-32;//A mayúsculas 
              }
            }else if((c>='A'&&c<='Z')){
                if(cad[i-1]!=' ' && i!=0){
                    c =c+32;//A minúsculas 
                }
            }
            printf("%c", c);
            cad[i++] = c;
        }else if(c == ' '){
            printf("%c", c);
            cad[i++] = c;
        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }

    cad[i++]='\0';
    return cad;
}


// *******************DATA CONVERTION**********************
template <typename T>
T Validation<T>::data_convertion_to_number(char *value, char *data_type){
    if(!strcmp(data_type, "int")){
        int int_value = atoi(value);
        return int_value;
    }else if(!strcmp(data_type, "float")) {
        float float_value = atof(value);
        return float_value;
    }   
    return 0;
}


template <typename T>
bool Validation<T>::validate_isbn(const string &isbn) {
    int length = isbn.length();

    // Validación de ISBN-10
    if (length == 10) {
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            if (!isdigit(isbn[i])) return false; // Solo dígitos
            sum += (isbn[i] - '0') * (10 - i);
        }
        char last_char = isbn[9];
        if (last_char != 'X' && !isdigit(last_char)) return false;

        sum += (last_char == 'X') ? 10 : (last_char - '0');
        return (sum % 11 == 0);
    }
    // Validación de ISBN-13
    else if (length == 13) {
        int sum = 0;
        for (int i = 0; i < 13; i++) {
            if (!isdigit(isbn[i])) return false; // Solo dígitos
            int digit = isbn[i] - '0';
            sum += (i % 2 == 0) ? digit : digit * 3;
        }
        return (sum % 10 == 0);
    }

    // Longitud inválida
    return false;
}