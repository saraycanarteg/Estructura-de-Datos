#include <iostream>
using namespace std;

template <class T>
class Caja {
private:
    T valor;
    T largo;
    T ancho;
    T alto;

public:
    // Constructor

    // Métodos para obtener los valores de cada atributo
    T obtenerValor() { return valor; }
    T obtenerLargo() { return largo; }
    T obtenerAncho() { return ancho; }
    T obtenerAlto() { return alto; }

    // Método para mostrar la información completa
    void mostrarInformacion() {
        cout << "Valor: " << valor << ", Largo: " << largo 
             << ", Ancho: " << ancho << ", Alto: " << alto << endl;
    }
};

int main() {
    // Instanciamos la clase con un entero
    Caja<int> cajaEntera(10, 5, 3, 7);
    cajaEntera.mostrarInformacion();

    // Instanciamos la clase con un flotante
    Caja<double> cajaDecimal(12.5, 6.3, 4.2, 9.1);
    cajaDecimal.mostrarInformacion();

    return 0;
}
