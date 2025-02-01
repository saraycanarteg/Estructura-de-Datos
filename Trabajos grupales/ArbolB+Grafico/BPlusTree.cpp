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
void BPlusTree<T, DEGREE>::splitChild(Node<T, DEGREE>* node, int index, Node<T, DEGREE>* child) {
    Node<T, DEGREE>* newChild = new Node<T, DEGREE>(child->isLeaf);
    newChild->numKeys = (DEGREE - 1) / 2;

    for (int j = 0; j < (DEGREE - 1) / 2; j++) {
        newChild->keys[j] = child->keys[j + (DEGREE + 1) / 2];
    }

    if (!child->isLeaf) {
        for (int j = 0; j <= (DEGREE - 1) / 2; j++) {
            newChild->children[j] = child->children[j + (DEGREE + 1) / 2];
        }
    }

    child->numKeys = (DEGREE - 1) / 2;

    for (int j = node->numKeys; j >= index + 1; j--) {
        node->children[j + 1] = node->children[j];
    }

    node->children[index + 1] = newChild;

    for (int j = node->numKeys - 1; j >= index; j--) {
        node->keys[j + 1] = node->keys[j];
    }

    node->keys[index] = child->keys[(DEGREE - 1) / 2];
    node->numKeys++;
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::traverse(Node<T, DEGREE>* node) const {
    int i;
    for (i = 0; i < node->numKeys; i++) {
        if (!node->isLeaf) {
            traverse(node->children[i]);
        }
        std::cout << " " << node->keys[i];
    }

    if (!node->isLeaf) {
        traverse(node->children[i]);
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::display() const {
    if (root != nullptr) {
        traverse(root);
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::printStructure(Node<T, DEGREE>* node, int level) const {
    if (node != nullptr) {
        std::cout << "Nivel " << level << ": ";
        for (int i = 0; i < node->numKeys; i++) {
            std::cout << node->keys[i] << " ";
        }
        std::cout << std::endl;
        if (!node->isLeaf) {
            for (int i = 0; i <= node->numKeys; i++) {
                printStructure(node->children[i], level + 1);
            }
        }
    }
}

template <typename T, int DEGREE>
void BPlusTree<T, DEGREE>::displayStructure() const {
    printStructure(root, 0);
}

// Explicit template instantiation
template class BPlusTree<int, 3>;