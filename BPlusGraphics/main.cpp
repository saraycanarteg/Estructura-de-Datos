#include "BPlusTreeVisualizer.h"
#include <iostream>

int main() {
    BPlusTree<int, 3> tree;
    BPlusTreeVisualizer<int, 3> visualizer(tree);
    
    char choice;
    do {
        std::cout << "1. Insertar numero\n";
        std::cout << "2. Eliminar numero\n";
        std::cout << "3. Mostrar arbol\n";
        std::cout << "4. Mostrar recorrido\n";
        std::cout << "5. Salir\n";
        std::cout << "Elija una opcion: ";
        std::cin >> choice;
        
        switch(choice) {
            case '1': {
                int number;
                std::cout << "Ingrese un numero: ";
                std::cin >> number;
                visualizer.visualizeInsertion(number);
                break;
            }
            case '2':
                int number;
                std::cout << "Ingrese el numero a eliminar: ";
                std::cin >> number;
                visualizer.visualizeRemoval(number);
                break;
            case '3':
                visualizer.displayTree();
                break;
            case '4':
                visualizer.displayTraversal();
                break;
            case '5':
                return 0;
        }
    } while (true);
    
    return 0;
}