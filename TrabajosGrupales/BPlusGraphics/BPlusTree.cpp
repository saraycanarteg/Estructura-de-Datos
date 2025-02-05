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
    Node<T, DEGREE>* newChild = new Node<T, DEGREE>(child->isLeaf);
    
    if (child->isLeaf) {
        // Punto de división corregido para hojas
        int splitPoint = (child->numKeys + 1) / 2; 
        newChild->numKeys = child->numKeys - splitPoint;
        
        // Copiar la segunda mitad al nuevo nodo
        for (int j = 0; j < newChild->numKeys; j++) {
            newChild->keys[j] = child->keys[j + splitPoint];
        }
        
        // Mantener la cadena de hojas
        newChild->children[DEGREE] = child->children[DEGREE];
        child->children[DEGREE] = newChild;
        
        // Ajustar claves en el nodo original
        child->numKeys = splitPoint;
        
        // Clave promovida (primera del nuevo nodo)
        T promoteKey = newChild->keys[0];
        
        // Insertar promoteKey en el padre
        for (int j = node->numKeys; j > index; j--) {
            node->children[j + 1] = node->children[j];
            node->keys[j] = node->keys[j - 1];
        }
        node->keys[index] = promoteKey;
        node->children[index + 1] = newChild;
        node->numKeys++;
    } else {
        // Lógica para nodos internos (sin cambios)
        // ...
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::insertInternal(const T& key, Node<T, DEGREE>* node, Node<T, DEGREE>* child) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        // Inserción ordenada en hoja
        while (i >= 0 && key <= node->keys[i]) { // Cambiado < por <= para mover a la izquierda
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
        
        // Verificar si la hoja necesita split después de la inserción
        if (node->numKeys > DEGREE) {  // Split si excede el grado
            Node<T, DEGREE>* parent = findParent(root, node);
            if (!parent) {
                // Manejar split de raíz
                Node<T, DEGREE>* newRoot = new Node<T, DEGREE>(false);
                newRoot->children[0] = node;
                splitChild(newRoot, 0, node);
                root = newRoot;
            } else {
                int idx = getChildIndex(parent, node);
                splitChild(parent, idx, node);
            }
        }
    } else {
        // Lógica para nodos internos
        while (i >= 0 && key <= node->keys[i]) i--;
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
Node<T, DEGREE>* BPlusTree<T, DEGREE>::findParent(Node<T, DEGREE>* current, Node<T, DEGREE>* child) {
    if (current->isLeaf || current->children[0]->isLeaf) {
        return nullptr;
    }

    for (int i = 0; i <= current->numKeys; i++) {
        if (current->children[i] == child) {
            return current;
        }
        Node<T, DEGREE>* parent = findParent(current->children[i], child);
        if (parent != nullptr) {
            return parent;
        }
    }
    return nullptr;
}

template <typename T, int DEGREE>
int BPlusTree<T, DEGREE>::getChildIndex(Node<T, DEGREE>* parent, Node<T, DEGREE>* child) {
    for (int i = 0; i <= parent->numKeys; i++) {
        if (parent->children[i] == child) {
            return i;
        }
    }
    return -1;
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
void BPlusTree<T, DEGREE>::remove(const T& key) {
    if (!root) return;

    Node<T, DEGREE>* current = root;
    std::vector<Node<T, DEGREE>*> path;
    
    // Encontrar el nodo hoja y registrar el camino
    while (!current->isLeaf) {
        path.push_back(current);
        int idx = findKey(current, key);
        current = current->children[idx];
    }
    path.push_back(current);
    
    // Buscar la clave en el nodo hoja
    int leafIndex = -1;
    for (int i = 0; i < current->numKeys; i++) {
        if (current->keys[i] == key) {
            leafIndex = i;
            break;
        }
    }
    
    if (leafIndex == -1) return;  // Clave no encontrada
    
    // Eliminar la clave del nodo hoja
    for (int i = leafIndex; i < current->numKeys - 1; i++) {
        current->keys[i] = current->keys[i + 1];
    }
    current->numKeys--;
    
    // Si el nodo raíz es una hoja y está vacío
    if (current == root && current->numKeys == 0) {
        delete root;
        root = nullptr;
        return;
    }
    
    // Si el nodo hoja tiene suficientes claves, terminamos
    if (current->numKeys >= (DEGREE - 1) / 2) return;
    
    // Reequilibrar el árbol
    rebalanceAfterDeletion(path);
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::rebalanceAfterDeletion(std::vector<Node<T, DEGREE>*>& path) {
    while (path.size() > 1) {
        Node<T, DEGREE>* child = path.back();
        path.pop_back();
        Node<T, DEGREE>* parent = path.back();
        int childIndex = getChildIndex(parent, child);
        
        // Intentar tomar prestado del hermano izquierdo
        if (childIndex > 0) {
            Node<T, DEGREE>* leftSibling = parent->children[childIndex - 1];
            if (leftSibling->numKeys > (DEGREE - 1) / 2) {
                borrowFromPrev(parent, childIndex);
                return;
            }
        }
        
        // Intentar tomar prestado del hermano derecho
        if (childIndex < parent->numKeys) {
            Node<T, DEGREE>* rightSibling = parent->children[childIndex + 1];
            if (rightSibling->numKeys > (DEGREE - 1) / 2) {
                borrowFromNext(parent, childIndex);
                return;
            }
        }
        
        // Si no se puede tomar prestado, fusionar
        if (childIndex > 0) {
            merge(parent, childIndex - 1);
        } else {
            merge(parent, childIndex);
        }
        
        // Manejar caso especial de la raíz
        if (parent == root && parent->numKeys == 0) {
            Node<T, DEGREE>* oldRoot = root;
            root = !root->isLeaf ? root->children[0] : nullptr;
            delete oldRoot;
            break;
        }
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::removeFromLeaf(Node<T, DEGREE>* node, const T& key) {
    int idx = findKey(node, key);
    
    // Si la clave no está en este nodo
    if (idx >= node->numKeys || node->keys[idx] != key) return;
    
    // Desplazar las claves restantes
    for (int i = idx; i < node->numKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    node->numKeys--;
    
    // Si el nodo quedó con muy pocas claves
    if (node->numKeys < (DEGREE - 1) / 2) {
        Node<T, DEGREE>* parent = findParent(root, node);
        if (parent) {
            int nodeIdx = getChildIndex(parent, node);
            fill(parent, nodeIdx);
        }
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::fill(Node<T, DEGREE>* parent, int idx) {
    Node<T, DEGREE>* node = parent->children[idx];
    
    // Intentar tomar prestado del hermano izquierdo
    if (idx > 0 && parent->children[idx - 1]->numKeys > (DEGREE - 1) / 2) {
        borrowFromPrev(parent, idx);
    }
    // Intentar tomar prestado del hermano derecho
    else if (idx < parent->numKeys && parent->children[idx + 1]->numKeys > (DEGREE - 1) / 2) {
        borrowFromNext(parent, idx);
    }
    // Si no se puede tomar prestado, fusionar con un hermano
    else {
        if (idx > 0) {
            merge(parent, idx - 1);
        } else {
            merge(parent, idx);
        }
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::borrowFromPrev(Node<T, DEGREE>* parent, int idx) {
    Node<T, DEGREE>* child = parent->children[idx];
    Node<T, DEGREE>* sibling = parent->children[idx - 1];
    
    // Desplazar claves en el nodo actual
    for (int i = child->numKeys; i > 0; i--) {
        child->keys[i] = child->keys[i - 1];
    }
    
    // Mover la última clave del hermano
    child->keys[0] = sibling->keys[sibling->numKeys - 1];
    parent->keys[idx - 1] = child->keys[0];  // Actualizar clave en el padre
    
    sibling->numKeys--;
    child->numKeys++;
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::borrowFromNext(Node<T, DEGREE>* parent, int idx) {
    Node<T, DEGREE>* child = parent->children[idx];
    Node<T, DEGREE>* sibling = parent->children[idx + 1];
    
    // Añadir la primera clave del hermano al final del nodo actual
    child->keys[child->numKeys] = sibling->keys[0];
    parent->keys[idx] = sibling->keys[1];  // Actualizar clave en el padre
    
    // Desplazar claves en el hermano
    for (int i = 0; i < sibling->numKeys - 1; i++) {
        sibling->keys[i] = sibling->keys[i + 1];
    }
    
    sibling->numKeys--;
    child->numKeys++;
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::merge(Node<T, DEGREE>* parent, int idx) {
    Node<T, DEGREE>* child = parent->children[idx];
    Node<T, DEGREE>* sibling = parent->children[idx + 1];
    
    // Copiar claves del hermano
    for (int i = 0; i < sibling->numKeys; i++) {
        child->keys[child->numKeys + i] = sibling->keys[i];
    }
    
    // Actualizar punteros de hoja si es necesario
    if (child->isLeaf) {
        child->children[DEGREE] = sibling->children[DEGREE];
    }
    
    // Eliminar la clave del padre y ajustar los punteros
    for (int i = idx; i < parent->numKeys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
        parent->children[i + 1] = parent->children[i + 2];
    }
    
    child->numKeys += sibling->numKeys;
    parent->numKeys--;
    
    delete sibling;
}

template <typename T, int DEGREE>
int BPlusTree<T, DEGREE>::findKey(Node<T, DEGREE>* node, const T& key) {
    int idx = 0;
    while (idx < node->numKeys && node->keys[idx] <= key) {
        idx++;
    }
    return idx;
}