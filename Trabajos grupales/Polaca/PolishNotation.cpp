#include "PolishNotationConverter.h"
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <stdexcept>

int PolishNotationConverter::getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

std::string PolishNotationConverter::convertToPolishNotation(const std::string& expression) {
    std::stack<char> operators;
    std::string polishNotation;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            // Si es un número, agregarlo directamente
            polishNotation += token + " ";
        } else if (token[0] == '(') {
            operators.push(token[0]);
        } else if (token[0] == ')') {
            // Sacar operadores hasta encontrar el paréntesis de apertura
            while (!operators.empty() && operators.top() != '(') {
                polishNotation += std::string(1, operators.top()) + " ";
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        } else {
            // Operadores
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(token[0])) {
                polishNotation += std::string(1, operators.top()) + " ";
                operators.pop();
            }
            operators.push(token[0]);
        }
    }

    // Agregar los operadores restantes
    while (!operators.empty()) {
        polishNotation += std::string(1, operators.top()) + " ";
        operators.pop();
    }

    return polishNotation;
}

double PolishNotationConverter::evaluatePolishNotation(const std::string& polishNotation) {
    std::stack<double> values;
    std::istringstream iss(polishNotation);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            values.push(std::stod(token));
        } else {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();

            switch (token[0]) {
                case '+': values.push(a + b); break;
                case '-': values.push(a - b); break;
                case '*': values.push(a * b); break;
                case '/': 
                    if (b != 0) values.push(a / b); 
                    else throw std::runtime_error("División por cero");
                    break;
                case '^': values.push(std::pow(a, b)); break;
            }
        }
    }

    return values.top();
}

void PolishNotationConverter::run() {
    std::string input;
    std::cout << "Ingrese una expresión matemática (use espacios entre números y operadores)\n";
    std::cout << "Ejemplo: 3 + 4 * 2 / ( 1 - 5 ) ^ 2\n";
    std::cout << "Expresión: ";
    
    std::getline(std::cin, input);

    try {
        // Convertir a notación polaca
        std::string polishNotation = convertToPolishNotation(input);
        std::cout << "\nNotación Polaca: " << polishNotation << std::endl;

        // Evaluar la expresión en notación polaca
        double resultado = evaluatePolishNotation(polishNotation);
        std::cout << "Resultado: " << resultado << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}