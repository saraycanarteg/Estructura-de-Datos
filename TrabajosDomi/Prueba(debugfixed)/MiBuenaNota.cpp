//Crear un programa en c++ para insertar 5 elementos enteros en un arbol de busqueda binaria

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }

    void inorder() {
        inorderRec(root);
    }

private:
    Node* root;

    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
    }
};

int main() {
    BinaryTree tree;
    int elements[5] = {10, 5, 20, 3, 7};

    for (int i = 0; i < 5; ++i) {
        tree.insert(elements[i]);
    }

    std::cout << "Inorder traversal of the binary search tree: ";
    tree.inorder();
    std::cout << std::endl;

    return 0;
}