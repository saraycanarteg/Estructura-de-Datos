#include <iostream>
using namespace std;

class Persona {

private:
    // Atributos
    string nombre;
    int edad;

public:

    // Constructor vacío
    Persona() {
    }

    //Setter
    void setNameAndAge(string name, int age){
        nombre = name;
        edad = age;
    }
    // Método
    void mostrarInformacion() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << endl;
    }
};

int main() {
    // Instancia de la clase Persona
    Persona persona1;

    persona1.setNameAndAge("Danny", 19);

    persona1.mostrarInformacion();

    return 0;
}
