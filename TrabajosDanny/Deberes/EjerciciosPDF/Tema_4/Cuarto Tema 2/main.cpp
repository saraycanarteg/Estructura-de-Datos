#include <iostream>

// Simulación de la condición (i), suponiendo que siempre devuelve true
bool condicion(int i) {
    return true; // Puede modificarse según la lógica requerida
}

// Simulación del procesamiento
void procesa(int i, int j, int k) {
    // Simulación de las dos operaciones
}

// Función que implementa el código dado en el problema
template <typename Func1, typename Func2>
int contarOperaciones(int n, Func1 condicion, Func2 procesa) {
    int operaciones = 0;
    
    for (int i = 0; i < n; i++) { // n operaciones
        for (int j = i + 1; j <= n; j++) { // (n - i) operaciones por cada i
            if (condicion(i)) { // Una operación si la condición se evalúa
                operaciones++;
            }
            for (int k = 0; k < j; k++) { // j operaciones por cada (i, j)
                procesa(i, j, k); // Dos operaciones por llamada
                operaciones += 2;
            }
        }
    }
    return operaciones;
}

int main() {
    int n;
    std::cout << "Ingrese el valor de n: ";
    std::cin >> n;
    
    int totalOperaciones = contarOperaciones(n, condicion, procesa);
    std::cout << "Numero total de operaciones T(n): " << totalOperaciones << std::endl;
    
    return 0;
}
