#include <iostream>
#include <string>

#include "Generador_Correo.cpp"
#include "Nodo.cpp"
#include "Validation.cpp"

using namespace std;

int main(){


    string correo = "vacio", nombres, apellidos;

    Lista_Simple<string>* lista_correos_estudiantes = new Lista_Simple<string>();
    Generador_Correo generador = Generador_Correo(lista_correos_estudiantes);

    Validation<string> validacion_string;

    for (int i = 0 ; i<5 ; i++ ){
        cout<<"Ingrese sus nombres: ";
        nombres = validacion_string.enter_a_char_or_string(15);
        cout<<endl;

        cout<<"Ingrese sus apellidos: ";
        apellidos = validacion_string.enter_a_char_or_string(15);
        cout<<endl;

        correo = generador.generar_Correo(nombres, apellidos);

        if(!generador.identificar_correo_repetido(lista_correos_estudiantes, correo)){
            cout<<endl<<"Correo ya existente"<<endl;
            i--;
        }else{
            cout<<endl<<"Correo ingresado exitosamente"<<endl;
            
        }
        
    }

    lista_correos_estudiantes->mostrar();
    cout<<endl;

}
