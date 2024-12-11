#include <iostream>
#include <functional>
#include <queue>
#include <stack>
#include <stdexcept>

// Clase para envolver una función lambda recursiva
class RecursiveLambda {
public:
    // Constructor para inicializar la función lambda
    RecursiveLambda() {
        // Sobrecargamos el operador `()` con una lambda recursiva
        func = [this](int n) -> int {
            if (n <= 1) return 1;  // Caso base: factorial de 0 o 1 es 1
            return n * (*this)(n - 1);  // Llamada recursiva usando `this`
        };
    }

    // Sobrecarga del operador `()` para que la clase actúe como una función
    int operator()(int n) const {
        return func(n);
    }

private:
    std::function<int(int)> func;  // Función lambda recursiva
};

// Función para demostrar el uso de colas
void demonstrarCola() {
    std::queue<int> cola;
    
    std::cout << "\nDemostracion de Cola:\n";
    std::cout << "Ingrese 5 numeros para la cola:\n";
    
    for (int i = 0; i < 5; ++i) {
        int numero;
        std::cout << "Numero " << (i+1) << ": ";
        std::cin >> numero;
        cola.push(numero);
    }

    std::cout << "\nElementos en la cola:\n";
    while (!cola.empty()) {
        std::cout << cola.front() << " ";
        cola.pop();
    }
    std::cout << std::endl;
}

// Función para demostrar el uso de pilas
void demonstrarPila() {
    std::stack<int> pila;
    
    std::cout << "\nDemostracion de Pila:\n";
    std::cout << "Ingrese 5 numeros para la pila:\n";
    
    for (int i = 0; i < 5; ++i) {
        int numero;
        std::cout << "Numero " << (i+1) << ": ";
        std::cin >> numero;
        pila.push(numero);
    }

    std::cout << "\nElementos en la pila (orden inverso):\n";
    while (!pila.empty()) {
        std::cout << pila.top() << " ";
        pila.pop();
    }
    std::cout << std::endl;
}

int main() {
    RecursiveLambda factorial;
    int numero;

    // Solicitar número para factorial
    std::cout << "Ingrese un numero para calcular su factorial: ";
    std::cin >> numero;

    // Validar entrada
    if (numero < 0) {
        std::cerr << "Error: El factorial no esta definido para numeros negativos." << std::endl;
        return 1;
    }

    // Calcular y mostrar factorial
    try {
        std::cout << "Factorial de " << numero << " es: " << factorial(numero) << std::endl;
    } catch (const std::overflow_error& e) {
        std::cerr << "Error: Desbordamiento al calcular factorial." << std::endl;
    }

    // Demostrar uso de cola y pila
    demonstrarCola();
    demonstrarPila();

    return 0;
}