#include "PolishNotationConverter.h"
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <algorithm>

int PolishNotationConverter::getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool PolishNotationConverter::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Conversión a notación polaca inversa (postfijo)
std::string PolishNotationConverter::convertToPostfix(const std::string& expression) {
    std::stack<char> operators;
    std::string postfix;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            postfix += token + " ";
        } else if (token[0] == '(') {
            operators.push(token[0]);
        } else if (token[0] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += std::string(1, operators.top()) + " ";
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        } else if (isOperator(token[0])) {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(token[0])) {
                postfix += std::string(1, operators.top()) + " ";
                operators.pop();
            }
            operators.push(token[0]);
        }
    }

    while (!operators.empty()) {
        postfix += std::string(1, operators.top()) + " ";
        operators.pop();
    }

    return postfix;
}

// Conversión a notación polaca (prefijo)
std::string PolishNotationConverter::convertToPrefix(const std::string& expression) {
    std::stack<std::string> operands;
    std::stack<char> operators;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            operands.push(token);
        } else if (token[0] == '(') {
            operators.push(token[0]);
        } else if (token[0] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                std::string op = std::string(1, operators.top());
                operators.pop();

                std::string b = operands.top(); operands.pop();
                std::string a = operands.top(); operands.pop();

                operands.push(op + " " + a + " " + b);
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        } else if (isOperator(token[0])) {
            while (!operators.empty() && getPrecedence(operators.top()) > getPrecedence(token[0])) {
                std::string op = std::string(1, operators.top());
                operators.pop();

                std::string b = operands.top(); operands.pop();
                std::string a = operands.top(); operands.pop();

                operands.push(op + " " + a + " " + b);
            }
            operators.push(token[0]);
        }
    }

    while (!operators.empty()) {
        std::string op = std::string(1, operators.top());
        operators.pop();

        std::string b = operands.top(); operands.pop();
        std::string a = operands.top(); operands.pop();

        operands.push(op + " " + a + " " + b);
    }

    return operands.top();
}

double PolishNotationConverter::evaluatePostfix(const std::string& postfix) {
    std::stack<double> values;
    std::istringstream iss(postfix);
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
                    else throw std::runtime_error("Division por cero");
                    break;
                case '^': values.push(std::pow(a, b)); break;
            }
        }
    }

    return values.top();
}

void PolishNotationConverter::run() {
    std::string input;
    std::cout << "Ingrese una expresion matematica (use espacios entre numeros y operadores)\n";
    std::cout << "Ejemplo: 3 + 4 * 2 / ( 1 - 5 ) ^ 2\n";
    std::cout << "Expresion: ";
    
    std::getline(std::cin, input);

    try {
        // Convertir a notación polaca inversa (postfijo)
        std::string postfix = convertToPostfix(input);
        //std::cout << "\nNotacion Polaca Inversa (Postfijo): " << postfix << std::endl;

        // Evaluar la expresión en notación polaca inversa
        double resultadoPostfix = evaluatePostfix(postfix);
        std::cout << "Resultado: " << resultadoPostfix << std::endl;

        // Convertir a notación polaca (prefijo)
        std::string prefix = convertToPrefix(input);
        std::cout << "\nNotacion Polaca (Prefijo): " << prefix << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
