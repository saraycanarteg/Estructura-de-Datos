#include "ListaSimple.cpp"

using namespace std;

class Persona{
    private:
        string nombre;
        string apellido;
    public:

    Persona(string nombre,string apellido): nombre(nombre), apellido(apellido){}
};

int main(){
    Persona persona1("Danny", "Ayuquina");
    Persona persona2("Marco", "Aurelio");
    Persona persona3("Moises", "Caicedo");

    ListaSimple<Persona> lista_simple;
    lista_simple.insertar(persona1);
    lista_simple.insertar(persona2);
    lista_simple.insertar(persona3);


    return 0;
}