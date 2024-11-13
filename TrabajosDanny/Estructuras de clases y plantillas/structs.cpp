#include <iostream>
#include <string>
using namespace std;

// Definición de un struct
struct Persona {
    string nombre;
    int edad;
    char genero;

    // Constructor del struct
    Persona(string nom, int ed, char gen) : nombre(nom), edad(ed), genero(gen) {}

    // Método para mostrar información
    void mostrarInformacion() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << ", Género: " << genero << endl;
    }
};

int main() {
    // Creación de un objeto de tipo struct
    Persona persona1("Carlos", 25, 'M');

    // Acceso directo a los miembros del struct
    cout << "Nombre: " << persona1.nombre << endl;
    cout << "Edad: " << persona1.edad << endl;

    // Llamada al método del struct
    persona1.mostrarInformacion();

    return 0;
}
