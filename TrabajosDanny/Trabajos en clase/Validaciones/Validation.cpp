#include <iostream>
#include <string.h>
#include "Validation.h"

using namespace std;

template <typename T>
Validation<T>::Validation(){}

template <typename T>
T Validation<T>::enter_a_number(char *data_type){
    char cad[10], c;
    int i = 0;
    bool validation_decimal=false;

    while(((c = getch())!=13)){
        
        if (c>='0' && c <= '9' ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c == '.' && (validation_decimal==false) && (strcmp(data_type, "float")||strcmp(data_type, "double"))){
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
T Validation<T>::enter_a_char_or_string(char *data_type){
    char cad[10], c;
    int i = 0;
     while(((c = getch())!=13)){
        if ((c>='a' && c <= 'z') || (c>='A'&&c<='Z') /*|| (c==' ')*/ ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }
    cad[i++]='\0';
    T return_data = data_convertion_to_string(cad, data_type);
    return return_data;
}

template <typename T>
T Validation<T>::data_convertion_to_string(char value[], char *data_type){
    string string_value="";
    if(strcmp(data_type, "string")){ 
        for(int j = 0; value[j] != '\0';j++){
            string_value = string_value + value[j];
        }
        return string_value;
    }else if(strcmp(data_type, "char")){ 
        return value;
    }
    return 0;
}

template <typename T>
T Validation<T>::data_convertion_to_number(char value[], char *data_type){
    if(strcmp(data_type, "int")){
        int int_value = atoi(value);
        return int_value;
    }else if(strcmp(data_type, "float")) {
        float float_value = atof(value);
        return float_value;
    }   
    return 0;
}