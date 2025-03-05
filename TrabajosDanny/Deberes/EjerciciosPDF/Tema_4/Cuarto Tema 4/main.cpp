#include <iostream>
#include <cmath>

// Función que calcula T(n) usando la solución obtenida en la imagen
double T(int n) {
    const double C1 = -1.0 / 15.0;
    const double C2 = 16.0 / 15.0;
    return C1 + C2 * (n * n);
}

int main() {
    int n;
    std::cout << "Ingrese el valor de n: ";
    std::cin >> n;
    
    if (n < 1) {
        std::cout << "n debe ser mayor o igual a 1" << std::endl;
        return 1;
    }
    
    double resultado = T(n);
    std::cout << "T(" << n << ") = " << resultado << std::endl;
    
    return 0;
}
