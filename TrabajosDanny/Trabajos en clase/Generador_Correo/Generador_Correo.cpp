#include <iostream>
#include "Generador_Correo.h"

using namespace std;

Generador_Correo::Generador_Correo(){}

Generador_Correo::Generador_Correo(Lista_Simple<string>* _lista_correo){
    lista_correo = _lista_correo;
}

void Generador_Correo::set_Lista_Correo(Lista_Simple<string>* _lista_correo){
    lista_correo = _lista_correo;
}

Lista_Simple<string>* Generador_Correo::get_Lista_Correo(){
    return lista_correo;
}

void Generador_Correo::separar_palabras(string palabras_unidas, string& palabra_1, string& palabra_2){

    size_t posicion = palabras_unidas.find(32); 

    if (posicion != std::string::npos) { 
        palabra_1 = palabras_unidas.substr(0, posicion);       
        palabra_2 = palabras_unidas.substr(posicion + 1);      
    } else {
        palabra_1 = palabras_unidas; 
        palabra_2 = "";              
    }


}

string Generador_Correo::generar_Correo(string nombres, string apellidos){

    string correo, palabra_1, palabra_2;

    separar_palabras(nombres, palabra_1, palabra_2);

    correo = string(1, palabra_1[0]+32) + string(1, palabra_2[0]+32);

    separar_palabras(apellidos, palabra_1, palabra_2);

    palabra_1[0] = tolower(palabra_1[0]);

    correo = correo + palabra_1;

    correo = correo + "@espe.edu.ec";


    return correo;

}

bool Generador_Correo::identificar_correo_repetido(Lista_Simple<string>* lista_correo, string correo){

    if(lista_correo->buscar(correo)){
        return false;
    }else{
        lista_correo->insertar_cabeza(correo);
        return true;
    }
}