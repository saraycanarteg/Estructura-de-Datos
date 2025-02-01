#include <iostream>
#include "BplusTree.cpp"

int main() {
    BPlusTree<int, 3> tree;

    // Insertar elementos en el árbol B+
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    // Mostrar el contenido del árbol B+
    std::cout << "Contenido del arbol B+:" << std::endl;
    tree.display();
    std::cout << std::endl;

    // Mostrar la estructura del árbol B+
    std::cout << "Estructura del arbol B+:" << std::endl;
    tree.displayStructure();
    std::cout << std::endl;

    return 0;
}