#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int ingreso_por_teclado(char *, char[]);

int ingreso_por_teclado(char *msj, char cadena[]){
    printf("%s", msj);
    char cad[10], c;
    int valor, i = 0;

    while(((c = getch())!=13)){
        if ((c>='0' && c <= '9')|| c == '\b'){
            printf("%c", c);
            cad[i++] = c;
        }
    }

    cad[i++]='\0';
    strcpy(cadena, cad);
    valor = atoi(cad);
    return valor;
}

int main(){
    char cadena[10];
    printf("\n%d\n", ingreso_por_teclado("Ingrese un valor dato de cualquier tipo ", cadena));

    cout<<cadena<<endl;

}
