#include<iostream>
#include<conio.h>
#include<string.h>
//Constantes
char mayusculas[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char minusculas[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char numeros[]={'0','1','2','3','4','5','6','7','8','9'};

using namespace std;

//Validación de letras
bool v_letras(int longitud, char palabra[]){

    int i, j, aux;

    for(i=0;i<longitud;i++){
        if(palabra[i]=='\0'){
            if(i==0){
                return false;
            }
            break;
        }
        for(j=0;j<26;j++){
            if(palabra[i]==mayusculas[j]||palabra[i]==minusculas[j]||palabra[i]==' '){
                aux=1;
                break;
            }
        }
        if(aux!=1){
            return false;
        }
        aux=0;
    }


    return true;
}
//Validación de números enteros
bool v_numeros(int longitud, char palabra[]){

    int i, j, aux;

    for(i=0;i<longitud;i++){
        if(palabra[i]=='\0'){
            if(i==0){
                return false;
            }
            break;
        }
        for(j=0;j<10;j++){
            if(palabra[i]==numeros[j]){
                aux=1;
                break;
            }
        }
        if(aux!=1){
            return false;
        }
        aux=0;
    }


    return true;
}



