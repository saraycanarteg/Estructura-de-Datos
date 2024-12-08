#include <iostream>
#include <functional>

class RecursiveLambda {
public:
    std::function<int(int)> operation;  // Define una función lambda recursiva.

    RecursiveLambda() = default;

    // Constructor que toma un lambda recursivo.
    RecursiveLambda(std::function<int(int)> func) : operation(std::move(func)) {}

    // Sobrecarga de operadores para crear combinaciones recursivas.
    RecursiveLambda operator+(const RecursiveLambda& other) const {
        return RecursiveLambda([=](int x) {
            return this->operation(x) + other.operation(x);
        });
    }

    RecursiveLambda operator-(const RecursiveLambda& other) const {
        return RecursiveLambda([=](int x) {
            return this->operation(x) - other.operation(x);
        });
    }

    RecursiveLambda operator*(const RecursiveLambda& other) const {
        return RecursiveLambda([=](int x) {
            return this->operation(x) * other.operation(x);
        });
    }

    RecursiveLambda operator/(const RecursiveLambda& other) const {
        return RecursiveLambda([=](int x) {
            return this->operation(x) / other.operation(x);
        });
    }

    // Operador de llamada para ejecutar el lambda encapsulado.
    int operator()(int x) const {
        return operation(x);
    }
};

int main() {
    // Define un factorial como una función lambda recursiva.
    RecursiveLambda factorial;
    factorial = RecursiveLambda([&factorial](int n) -> int {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    });

    // Define otro lambda que calcula el doble de un número.
    RecursiveLambda doubleFunc([](int n) {
        return 2 * n;
    });

    // Prueba las sobrecargas de operadores.
    RecursiveLambda combined = factorial + doubleFunc;

    std::cout << "Factorial de 5: " << factorial(5) << std::endl;  // 120
    std::cout << "Doble de 5: " << doubleFunc(5) << std::endl;     // 10
    std::cout << "Combinación (factorial + doble) de 5: " << combined(5) << std::endl; // 130

    return 0;
}
