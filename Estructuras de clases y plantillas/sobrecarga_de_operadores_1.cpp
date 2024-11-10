#include <iostream>

using namespace std;

template <class T>
class Caja {
private:
    T valor;
public:
    Caja(T v) : valor(v) {}

    // Sobrecarga del operador +
    Caja operator+(const Caja& otraCaja) {
        return Caja(this->valor + otraCaja.valor);
    }

    T obtenerValor() {
        return valor;
    }
};

int main() {
    Caja<int> caja1(10);
    Caja<int> caja2(20);
    Caja<int> cajaSuma = caja1 + caja2; // Sobrecarga del operador +
    cout << "Suma de las cajas: " << cajaSuma.obtenerValor() << endl;

    return 0;
}
