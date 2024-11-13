#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int ingreso_por_teclado_int(){
    char cad[10], c;
    int valor, i = 0/*, j*/ ;

    while(((c = getch())!=13)){

        if ((c>='0' && c <= '9')){
            printf("%c", c);
            cad[i++] = c;
        }/*else if(c=='\b'&&i>=0){
            cad[i--]=0;
            for(j=0;j<strlen(cad);j++){
                cout<<endl<<cad[j];
            }
        }*/
        
    }

    cad[i++]='\0';
    valor = atoi(cad);
    return valor;
}