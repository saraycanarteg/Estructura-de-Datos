#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

void ingreso_de_dato_por_teclado();
bool identificacion_primer_caracter(char []);
void conversion_de_datos(int, char[], int &, float &);

int main(){
    cout<<"Ingrese un tipo de dato numerico o string: ";
    ingreso_de_dato_por_teclado();
}

void conversion_de_datos(int tipo_de_dato, char valor[], int &valor_convertido_int, float &valor_convertido_float){
    
    switch (tipo_de_dato){
    case 1:
        valor_convertido_int = atoi(valor);
        break;
    case 2: 
        valor_convertido_float = atof(valor);
        break;
    default:
        break;
    }
}

bool identificacion_primer_caracter(char cadena[]){
    int comp;

    if(cadena[0]>='0'&& cadena[0]<='9'){
        comp = true;
    }else if (cadena[0]>='a'&& cadena[0]<='z'){
        comp = false;
    }
    return comp;
}

void ingreso_de_dato_por_teclado(){
    char cad[10], c;
    int i = 0, tipo_de_dato = 1;
    int valor_convertido_int;
    float valor_convertido_float;
    bool validadion_punto_decimal=false;

    while(((c = getch())!=13)){
        
        if(i==0){
            cad[i]=c;
            printf("%c", c);
            i++;

        }else if (c>='0' && c <= '9' && identificacion_primer_caracter(cad)){
            printf("%c", c);
            cad[i++] = c;

        }else if(c == '.' && !validadion_punto_decimal){
            printf("%c", c);
            cad[i++] = c;
            validadion_punto_decimal=true;
            tipo_de_dato=2;

        }else if(c>='a' && c <= 'z' && (!identificacion_primer_caracter(cad))){
            printf("%c", c);
            cad[i++] = c;
            tipo_de_dato = 3;
        }
        if(i==12){
            break;
        }

    }

    cad[i++]='\0';
    cout<<endl;

    conversion_de_datos(tipo_de_dato, cad, valor_convertido_int, valor_convertido_float);

    if(tipo_de_dato == 1){
        cout<<valor_convertido_int+1<<endl;
    }else if(tipo_de_dato == 2){
        cout<<valor_convertido_float+1<<endl;
    }else{
        cout<<cad<<endl;
    }

}

