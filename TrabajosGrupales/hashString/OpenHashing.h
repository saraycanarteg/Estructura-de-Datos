#ifndef OPENHASHING_H
#define OPENHASHING_H

#include <string>
#include <bitset>


struct Node {
    std::string key;
    Node* next;
    Node(const std::string& k) : key(k), next(nullptr) {}
};

class OpenHashing {
private:
    Node** table;
    int size;
    int hashFunction(const std::string& key);
    std::string stringToBinary(const std::string& str);
    long binaryToDecimal(const std::string& binary);

public:
    OpenHashing(int s);
    void insert(const std::string& key);
    void display();
    ~OpenHashing();
    bool remove(const std::string& key);
};

#endif