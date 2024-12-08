#include <iostream>
#include "Lista_Simple.cpp"

using namespace std;

class Generador_Correo{

    private:

        Lista_Simple<string>* lista_correo;

    public:

        Generador_Correo();
        Generador_Correo(Lista_Simple<string>* lista_correo);

        void set_Lista_Correo(Lista_Simple<string>* _lista_correo);
        Lista_Simple<string>* get_Lista_Correo();

        string generar_Correo(string nombres, string apellidos);
        bool identificar_correo_repetido(Lista_Simple<string>* lista_correo, string correo);
        void separar_palabras(string palabras, string& palabra_1, string& palabra_2);
};