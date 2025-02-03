#include "BplusTree.h"

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::insert(const T& key) {
    Node<T, DEGREE>* r = root;
    if (r->numKeys == DEGREE) {
        Node<T, DEGREE>* s = new Node<T, DEGREE>(false);
        root = s;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertInternal(key, s, nullptr);
    } else {
        insertInternal(key, r, nullptr);
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::insertInternal(const T& key, Node<T, DEGREE>* node, Node<T, DEGREE>* child) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == DEGREE) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertInternal(key, node->children[i], child);
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::traverse(Node<T, DEGREE>* node) const {

    // Encontrar el primer nodo hoja (el más a la izquierda)
    Node<T, DEGREE>* leaf = node;
    while (!leaf->isLeaf) {
        leaf = leaf->children[0];
    }
    
    // Imprimir todos los valores en las hojas
    while (leaf != nullptr) {
        for (int i = 0; i < leaf->numKeys; i++) {
            std::cout << " " << leaf->keys[i];
        }
        leaf = leaf->children[DEGREE];
    }
    std::cout << std::endl;
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::splitChild(Node<T, DEGREE>* node, int index, Node<T, DEGREE>* child) {
    // Crear un nuevo nodo hijo derecho
    Node<T, DEGREE>* newChild = new Node<T, DEGREE>(child->isLeaf);

    // Punto de división
    int splitPoint = DEGREE / 2;

    // Copiar la mitad superior de las claves al nuevo nodo derecho
    newChild->numKeys = child->numKeys - splitPoint;
    for (int j = 0; j < newChild->numKeys; j++) {
        newChild->keys[j] = child->keys[j + splitPoint];
    }

    // Si es un nodo interno, copiar los hijos correspondientes
    if (!child->isLeaf) {
        for (int j = 0; j <= newChild->numKeys; j++) {
            newChild->children[j] = child->children[j + splitPoint];
        }
    } else {
        // Para nodos hoja, ajustar la lista enlazada
        newChild->children[DEGREE] = child->children[DEGREE];
        child->children[DEGREE] = newChild;
    }

    // Ajustar el número de claves del nodo original
    child->numKeys = splitPoint;

    // Insertar el nuevo hijo en el nodo padre
    for (int j = node->numKeys; j > index; j--) {
        node->children[j + 1] = node->children[j];
        node->keys[j] = node->keys[j - 1];  // Desplazar claves
    }
    node->children[index + 1] = newChild;

    // ✅ CORRECCIÓN: Promover la primera clave del nuevo nodo derecho
    node->keys[index] = newChild->keys[0];
    node->numKeys++;
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::printStructure(Node<T, DEGREE>* node, int level) const {
    if (node == nullptr) return;

    // Imprimir nodos internos nivel por nivel
    std::queue<std::pair<Node<T, DEGREE>*, int>> nodesQueue;
    nodesQueue.push(std::make_pair(node, level));
    int currentLevel = level;
    bool internalNodesPrinted = false;
    
    while (!nodesQueue.empty()) {
        Node<T, DEGREE>* current = nodesQueue.front().first;
        int nodeLevel = nodesQueue.front().second;
        nodesQueue.pop();
        
        if (nodeLevel > currentLevel) {
            if (internalNodesPrinted) std::cout << std::endl;
            currentLevel = nodeLevel;
        }
        
        // Solo imprimir los nodos internos
        if (!current->isLeaf) {
            internalNodesPrinted = true;
            std::cout << " Nivel " << nodeLevel << ": ";
            std::cout << "[";
            for (int i = 0; i < current->numKeys; i++) {
                std::cout << current->keys[i];
                if (i < current->numKeys - 1) std::cout << " ";
            }
            std::cout << "]";
            
            for (int i = 0; i <= current->numKeys; i++) {
                if (current->children[i]) {
                    nodesQueue.push(std::make_pair(current->children[i], nodeLevel + 1));
                }
            }
        }
    }
    
    // Imprimir nodos hoja con flechas
    Node<T, DEGREE>* leaf = node;
    while (!leaf->isLeaf) {
        leaf = leaf->children[0];
    }
    
    while (leaf != nullptr) {
        std::cout << "[";
        for (int i = 0; i < leaf->numKeys; i++) {
            std::cout << leaf->keys[i];
            if (i < leaf->numKeys - 1) std::cout << " ";
        }
        std::cout << "]";
        
        leaf = leaf->children[DEGREE];
        if (leaf != nullptr) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    std::cout <<  "Altura: " << calculateHeight(node) << ", Profundidad: " << calculateDepth(node) << std::endl;

}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::display() const {
    if (root != nullptr) {
        traverse(root);
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::displayStructure() const {
    printStructure(root, 0);
}

template <typename T, int DEGREE>
int BPlusTree<T, DEGREE>::calculateHeight(Node<T, DEGREE>* node) const {
    if (node == nullptr || node->isLeaf) return 0;
    int height = 0;
    for (int i = 0; i <= node->numKeys; i++) {
        if (node->children[i]) {
            int childHeight = calculateHeight(node->children[i]);
            height = std::max(height, childHeight);
        }
    }
    return height + 1;
}

template <typename T, int DEGREE>
int BPlusTree<T, DEGREE>::calculateDepth(Node<T, DEGREE>* node) const {
    if (node == nullptr) return 0;
    
    int maxDepth = 0;
    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            int childDepth = calculateDepth(node->children[i]);
            maxDepth = std::max(maxDepth, childDepth);
        }
        maxDepth++;
    }
    
    return maxDepth;
}
