#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm> // Add this include for std::sort
#include "Libro.h"

class BPlusTreeNode {
public:
    bool isLeaf;
    std::vector<std::string> keys;
    std::vector<BPlusTreeNode*> children;
    std::vector<std::pair<std::string, Libro>> data; // Cambiar a vector de pares

    BPlusTreeNode(bool leaf);
};


class BPlusTree {
private:
    BPlusTreeNode* root;
    int minDegree;

    void insertNonFull(BPlusTreeNode* node, const std::string& key, const Libro& value);
    void splitChild(BPlusTreeNode* node, int i, BPlusTreeNode* y);
    BPlusTreeNode* search(BPlusTreeNode* node, const std::string& key);
    void collectElements(BPlusTreeNode* node, std::vector<std::pair<std::string, Libro>>& elements);
    void clearTree(BPlusTreeNode* node);
    void saveNodeToFile(BPlusTreeNode* node, std::ofstream& archivo);
    BPlusTreeNode* loadNodeFromFile(std::ifstream& archivo);

public:
    BPlusTreeNode* getRoot() const;
    void setRoot(BPlusTreeNode* newRoot);

    void traverse(BPlusTreeNode* node, std::ostream& out);
    BPlusTree(int t);
    void insert(const std::string& key, const Libro& value);
    Libro search(const std::string& key);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void sort();
    // Trees objects
    void insertObject(const std::string& isbn, const Libro& libro);
    Libro searchObject(const std::string& isbn);
    void insertNonFullObject(BPlusTreeNode* node, const std::string& isbn, const Libro& libro);
    void saveNodeToFileObject(BPlusTreeNode* node, std::ofstream& archivo);
    void collectElementsObject(BPlusTreeNode* node, std::vector<std::pair<std::string, Libro>>& elements);
};;
