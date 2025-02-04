#include <iostream>
#include <windows.h> 
#include "BplusTree.cpp"

using namespace std;

void insertAndDisplay(BPlusTree<int, 3>& tree) {
    int number;
    char choice;

    cout << "Ingrese un numero para insertar en el arbol B+: ";
    cin >> number;
    tree.insert(number);

    // Mostrar el contenido del árbol B+
    cout << "Contenido del arbol B+ (INFIJO):" << endl;
    tree.display();
    cout << endl;

    // Mostrar la estructura del árbol B+
    cout << "Estructura del arbol B+:" << endl;
    tree.displayStructure();
    cout << endl;

    cout << "Desea agregar otro numero? (s/n): ";
    cin >> choice;

    if (choice == 's' || choice == 'S') {
        insertAndDisplay(tree);
    }
}

int main() {
    system("Color 0A"); 
    BPlusTree<int, 3> tree;
    insertAndDisplay(tree);
    return 0;
}