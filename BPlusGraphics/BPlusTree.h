#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include "Node.h"
#include <queue>
#include <cmath>
#include <iomanip>

template <typename T, int DEGREE>
class BPlusTree {
private:
    Node<T, DEGREE>* root;

    void insertInternal(const T& key, Node<T, DEGREE>* node, Node<T, DEGREE>* child);
    void splitChild(Node<T, DEGREE>* node, int index, Node<T, DEGREE>* child);
    void traverse(Node<T, DEGREE>* node) const;
    void printStructure(Node<T, DEGREE>* node, int level) const;
    Node<T, DEGREE>* findParent(Node<T, DEGREE>* current, Node<T, DEGREE>* child);
    int getChildIndex(Node<T, DEGREE>* parent, Node<T, DEGREE>* child);

    void removeFromLeaf(Node<T, DEGREE>* node, const T& key);
    void removeFromInternal(Node<T, DEGREE>* node, const T& key);
    T getPred(Node<T, DEGREE>* node, int idx);
    T getSucc(Node<T, DEGREE>* node, int idx);
    void borrowFromPrev(Node<T, DEGREE>* node, int idx);
    void borrowFromNext(Node<T, DEGREE>* node, int idx);
    void merge(Node<T, DEGREE>* node, int idx);
    void fill(Node<T, DEGREE>* node, int idx);
    int findKey(Node<T, DEGREE>* node, const T& key);
    void rebalanceAfterDeletion(std::vector<Node<T, DEGREE>*>& path);

public:
    BPlusTree() : root(new Node<T, DEGREE>(true)) {}
    ~BPlusTree() { delete root; }

    void insert(const T& key);
    void display() const;
    void displayStructure() const;
    int calculateHeight(Node<T, DEGREE>* node) const;
    int calculateDepth(Node<T, DEGREE>* node) const;
    int calculateLevel(Node<T, DEGREE>* node) const;;
    Node<T, DEGREE>* getRoot() const { return root; }
    void remove(const T& key);
};

#include "BPlusTree.cpp"
#endif // BPLUSTREE_H