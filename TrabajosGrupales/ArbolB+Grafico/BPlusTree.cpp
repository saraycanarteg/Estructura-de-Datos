#include "BplusTree.h"
#include <queue>
#include <cmath>
#include <iomanip>

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
void BPlusTree<T, DEGREE>::splitChild(Node<T, DEGREE>* node, int index, Node<T, DEGREE>* child) {
    // Create a new child node
    Node<T, DEGREE>* newChild = new Node<T, DEGREE>(child->isLeaf);
    
    // Calculate the split point
    int splitPoint = DEGREE / 2;
    
    // Copy upper half of keys to the new child
    newChild->numKeys = DEGREE - splitPoint - 1;
    for (int j = 0; j < newChild->numKeys; j++) {
        newChild->keys[j] = child->keys[j + splitPoint + 1];
    }

    // If it's an internal node, copy children
    if (!child->isLeaf) {
        for (int j = 0; j <= newChild->numKeys; j++) {
            newChild->children[j] = child->children[j + splitPoint + 1];
        }
        child->numKeys = splitPoint;
    } else {
        // For leaf nodes, adjust the linked list
        newChild->children[DEGREE] = child->children[DEGREE];
        child->children[DEGREE] = newChild;
        child->numKeys = splitPoint + 1;
    }

    // Make room for the new child in the parent node
    for (int j = node->numKeys; j > index; j--) {
        node->children[j + 1] = node->children[j];
    }
    node->children[index + 1] = newChild;

    // Move the splitting key up to the parent
    for (int j = node->numKeys - 1; j >= index; j--) {
        node->keys[j + 1] = node->keys[j];
    }
    node->keys[index] = child->keys[splitPoint];
    node->numKeys++;
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

template <typename T, int DEGREE>
int BPlusTree<T, DEGREE>::calculateLevel(Node<T, DEGREE>* node) const {
    std::queue<std::pair<Node<T, DEGREE>*, int>> queue;
    queue.push(std::make_pair(root, 0));
    
    while (!queue.empty()) {
        Node<T, DEGREE>* currentNode = queue.front().first;
        int level = queue.front().second;
        queue.pop();
        
        if (currentNode == node) return level;
        
        if (!currentNode->isLeaf) {
            for (int i = 0; i <= currentNode->numKeys; i++) {
                if (currentNode->children[i]) {
                    queue.push(std::make_pair(currentNode->children[i], level + 1));
                }
            }
        }
    }
    
    return -1; // Node not found
}

template <typename T, int DEGREE>
int BPlusTree<T, DEGREE>::getHeight() const {
    return calculateHeight(root);
}

template <typename T, int DEGREE>
int BPlusTree<T, DEGREE>::getDepth() const {
    return calculateDepth(root);
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::displayLevels() const {
    if (root == nullptr) return;
    
    std::queue<std::pair<Node<T, DEGREE>*, int>> queue;
    queue.push(std::make_pair(root, 0));
    int currentLevel = 0;
    
    while (!queue.empty()) {
        Node<T, DEGREE>* node = queue.front().first;
        int level = queue.front().second;
        queue.pop();
        
        if (level > currentLevel) {
            std::cout << std::endl;
            currentLevel = level;
        }
        
        // Print node contents
        std::cout << "[";
        for (int i = 0; i < node->numKeys; i++) {
            std::cout << node->keys[i];
            if (i < node->numKeys - 1) std::cout << " ";
        }
        std::cout << "]";
        
        // Add children to queue for internal nodes
        if (!node->isLeaf) {
            for (int i = 0; i <= node->numKeys; i++) {
                if (node->children[i]) {
                    queue.push(std::make_pair(node->children[i], level + 1));
                }
            }
        }
    }
    std::cout << std::endl;
}