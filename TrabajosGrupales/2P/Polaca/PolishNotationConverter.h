#ifndef POLISH_NOTATION_CONVERTER_H
#define POLISH_NOTATION_CONVERTER_H

#include <string>

class PolishNotationConverter {
private:
    // Función para determinar la precedencia de los operadores
    int getPrecedence(char op);
    bool isOperator(char c); 

    // Función para convertir la expresión a notación polaca
    std::string convertToPostfix(const std::string& expression); 
    std::string convertToPrefix(const std::string& expression); 

    // Función para evaluar una expresión en notación polaca
    double evaluatePostfix(const std::string& postfix);

public:
    // Método principal para ejecutar la conversión y evaluación
    void run();
};

#endif