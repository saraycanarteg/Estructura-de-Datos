#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm> // Add this include for std::sort

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
    std::string search(const std::string& key);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void sort();
};
