#ifndef NODE_H
#define NODE_H

template <typename T, int DEGREE>
class Node {
public:
    bool isLeaf;
    int numKeys;
    T keys[DEGREE];
    Node<T, DEGREE>* children[DEGREE + 1];
    Node<T, DEGREE>* next; // Pointer to the next leaf node

    Node(bool leaf) : isLeaf(leaf), numKeys(0), next(nullptr) {
        for (int i = 0; i < DEGREE + 1; ++i) {
            children[i] = nullptr;
        }
    }

    ~Node() {
        for (int i = 0; i < DEGREE + 1; ++i) {
            delete children[i];
        }
    }
};

#endif // NODE_H