#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>

int main() {
    double inicio, fin, paso;
    int numPuntos;
    
    // Pedir datos al usuario
    std::cout << "Ingrese el valor inicial para n (recomendado 0.1): ";
    std::cin >> inicio;
    
    std::cout << "Ingrese el valor final para n (recomendado 5.0): ";
    std::cin >> fin;
    
    std::cout << "Ingrese el número de puntos a calcular: ";
    std::cin >> numPuntos;
    
    // Calcular el paso
    paso = (fin - inicio) / (numPuntos - 1);
    
    // Abrir archivo CSV para guardar los datos
    std::ofstream archivo("datos_funcion.csv");
    archivo << "n,n_e,e_n,e_log_n" << std::endl;
    
    // Constante e
    const double e = 2.71828182845904523536;
    bool pertenece = true;
    double n0 = e; // Valor teórico donde e*log(n) ≤ n para todo n ≥ e
    
    // Calcular valores y guardar en el archivo
    for (int i = 0; i < numPuntos; i++) {
        double n = inicio + i * paso;
        double n_e = pow(n, e);          // n^e
        double e_n = pow(e, n);          // e^n
        double e_log_n = e * log(n);     // e*log(n)
        
        // Solo guardar valores válidos (evitar log de números negativos)
        if (n > 0) {
            archivo << std::fixed << std::setprecision(6) << n << "," 
                   << n_e << "," << e_n << "," << e_log_n << std::endl;
            
            // Verificar si n^e ≤ c*e^n para alguna constante c > 0 cuando n ≥ n0
            if (n >= n0 && n_e > e_n) {
                pertenece = false;
            }
        }
    }
    
    archivo.close();
    std::cout << "Datos guardados en 'datos_funcion.csv'" << std::endl;
    
    // Imprimir conclusión sobre la complejidad
    std::cout << "\n===== ANÁLISIS DE COMPLEJIDAD =====" << std::endl;
    std::cout << "Verificando si n^e ∈ O(e^n)..." << std::endl;
    
    if (pertenece) {
        std::cout << "RESULTADO: n^e SÍ pertenece a O(e^n)" << std::endl;
        std::cout << "Para todo n ≥ " << n0 << " (valor de e), se cumple que n^e ≤ c·e^n para alguna constante c > 0" << std::endl;
    } else {
        std::cout << "RESULTADO: n^e NO pertenece a O(e^n)" << std::endl;
        std::cout << "Se encontraron valores de n ≥ " << n0 << " donde n^e > c·e^n para cualquier constante c > 0" << std::endl;
    }
    
    std::cout << "\nGenerando grafico usando Python con matplotlib..." << std::endl;
    
    // Ejecutar el script de Python para visualizar
    std::string comando = "python graficador.py";
    system(comando.c_str());
    
    return 0;
}