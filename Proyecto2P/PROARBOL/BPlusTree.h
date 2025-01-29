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
    BPlusTreeNode* nextLeaf = nullptr;
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
    //void saveNodeToFile(BPlusTreeNode* node, std::ofstream& archivo);
    BPlusTreeNode* loadNodeFromFile(std::ifstream& archivo);
    
    void removeNode(BPlusTreeNode* node, const std::string& key);
    void removeFromLeaf(BPlusTreeNode* node, int idx);
    void removeFromNonLeaf(BPlusTreeNode* node, int idx);
    void fill(BPlusTreeNode* node, int idx);
    void borrowFromPrev(BPlusTreeNode* node, int idx);
    void borrowFromNext(BPlusTreeNode* node, int idx);
    void merge(BPlusTreeNode* node, int idx);
    int findKey(BPlusTreeNode* node, const std::string& key);
    std::string getSucc(BPlusTreeNode* node, int idx);
    std::string getPred(BPlusTreeNode* node, int idx);

public:
    BPlusTreeNode* getRoot() const;
    void setRoot(BPlusTreeNode* newRoot);

    void change_to_date(BPlusTreeNode* node);
    BPlusTree(int t);
    void search_by_first_word(BPlusTreeNode* node, const std::string& key);
    void easy_search(BPlusTreeNode* node, Libro& return_value, string key);
    void traverse();
    void insert(const std::string& key, const Libro& value);
    Libro search(const std::string& key);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void sort();
    void createBackup(const string& filename);
    void collectBooksByAuthor(BPlusTreeNode* node, const std::string& isni, vector<Libro>& librosEncontrados);
    vector<Libro> searchBooksByAuthor(const std::string& isni);
    void search_by_isbn_prefix(BPlusTreeNode* node, const std::string& prefix);
    void saveNodeToFile(BPlusTreeNode* node, std::ofstream& archivo);
    void eliminarLibro(BPlusTree& arbol, const string& isbn);
    // Trees objects
    void insertObject(const std::string& isbn, const Libro& libro);
    Libro searchObject(const std::string& isbn);
    void traverseHelper(BPlusTreeNode* node);
    void insertNonFullObject(BPlusTreeNode* node, const std::string& isbn, const Libro& libro);
    void saveNodeToFileObject(BPlusTreeNode* node, std::ofstream& archivo);
    void collectElementsObject(BPlusTreeNode* node, std::vector<std::pair<std::string, Libro>>& elements);
    void remove(const std::string& key);
    Libro searchByIsni(const std::string& isni);
};
