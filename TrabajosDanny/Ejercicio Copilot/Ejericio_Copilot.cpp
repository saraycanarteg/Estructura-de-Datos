#include <iostream>

int main() {
    int num1, num2, sum;

    std::cout << "Ingrese el primer numero: ";
    std::cin >> num1;

    std::cout << "Ingrese el segundo numero: ";
    std::cin >> num2;

    sum = num1 + num2;

    std::cout << "La suma de los dos numeros es: " << sum << std::endl;

    return 0;
}