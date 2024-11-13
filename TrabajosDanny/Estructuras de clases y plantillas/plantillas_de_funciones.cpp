#include <iostream>
using namespace std;

// Plantilla de función
template <typename T>
T suma(T a, T b) {
    return a + b;
}

int main() {
    int resultado_suma = suma<int>(3, 4);
    cout << "\nresultado suma con enteros: " << resultado_suma<<endl;

    float resultado_suma_float = suma<float>(3.5, 2.1);
    cout << "\nresultado suma con decimales: " << resultado_suma_float<<endl;

    return 0;
}
