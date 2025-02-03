#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "Node.h"
#include <iostream>

template <typename T, int DEGREE>
class BPlusTree {
private:
    Node<T, DEGREE>* root;

    void insertInternal(const T& key, Node<T, DEGREE>* node, Node<T, DEGREE>* child);
    void splitChild(Node<T, DEGREE>* node, int index, Node<T, DEGREE>* child);
    void traverse(Node<T, DEGREE>* node) const;
    void printStructure(Node<T, DEGREE>* node, int level) const;

    int calculateHeight(Node<T, DEGREE>* node) const;
    int calculateDepth(Node<T, DEGREE>* node) const;
    int calculateLevel(Node<T, DEGREE>* node) const;

public:
    BPlusTree() : root(new Node<T, DEGREE>(true)) {}
    ~BPlusTree() { delete root; }

    void insert(const T& key);
    void display() const;
    void displayStructure() const;
    int getHeight() const;
    int getDepth() const;
    void displayLevels() const;
};

#endif // BPLUSTREE_H