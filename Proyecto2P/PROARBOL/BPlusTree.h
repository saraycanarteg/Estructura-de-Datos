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
    std::map<std::string, std::string> data; // For leaf nodes

    BPlusTreeNode(bool leaf);
};

class BPlusTree {
private:
    BPlusTreeNode* root;
    int minDegree;

public:
    BPlusTreeNode* getRoot() const;
    void setRoot(BPlusTreeNode* newRoot);
    void insertNonFull(BPlusTreeNode* node, const std::string& key, const std::string& value);
    void splitChild(BPlusTreeNode* node, int i, BPlusTreeNode* y);
    void traverse(BPlusTreeNode* node, std::ofstream& archivo);
    BPlusTreeNode* search(BPlusTreeNode* node, const std::string& key);
    void collectElements(BPlusTreeNode* node, std::vector<std::pair<std::string, std::string>>& elements);
    void clearTree(BPlusTreeNode* node);
    void saveNodeToFile(BPlusTreeNode* node, std::ofstream& archivo);
    BPlusTreeNode* loadNodeFromFile(std::ifstream& archivo);

public:
    BPlusTree(int t);
    void insert(const std::string& key, const std::string& value);
    void insert_object(const std::string& key, Libro libro);
    std::string search(const std::string& key);
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
