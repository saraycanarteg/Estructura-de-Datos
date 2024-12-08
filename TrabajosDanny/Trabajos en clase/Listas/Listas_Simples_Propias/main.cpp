#include "Lista_Simple.cpp"
#include "Nodo.cpp"
#include <iostream>
#include "Validation.cpp"

using namespace std;

int main(){

    string palabra;

    Validation<string> validacion_string;

    Lista_Simple<string>* lista_string = new Lista_Simple<string>(); 

    for (int i = 0 ; i<5 ; i++){

        cout<<"Ingrese palabra: ";
        palabra = validacion_string.enter_a_char_or_string(10);
        lista_string->insertar_cabeza(palabra);
        cout<<endl;
    }

    lista_string->mostrar();
    
    char caracter;
    cout<<"Ingrese el caracter que quiere modificar en la lista: ";cin>>caracter;

    int desplazamiento;
    cout<<"Ingrese el desplazamiento del caracter: ";cin>>desplazamiento;

    auto desplazar_caracter = [&](char caracter, int desplazamiento) {
        
        char caracter_aux = caracter + desplazamiento;
        string dato;
        Lista_Simple<string>* lista_string_modificada = lista_string;
        Nodo<string>* aux = lista_string_modificada->get_Cabeza();

        while(aux != NULL){
            dato = aux->get_Dato();

            for (char& c:dato){
                if (c==caracter){
                    c=caracter_aux;
                }
            }

            aux->set_Dato(dato);

            aux = aux->get_Siguiente(); 
        }

        lista_string_modificada->mostrar();

    };

    desplazar_caracter(caracter, desplazamiento);

    cout<<lista_string->buscar("Danny")<<endl;


}
