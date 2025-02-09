#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <graphics.h>
#include <iostream>
#include <string>
#include <bitset>

class HashTable {
private:
    class HashNode {
    public:
        std::string key;
        bool occupied;
        HashNode(const std::string& k);
    };
    
    int size;
    HashNode** table;
    int hashFunction(const std::string& key);

public:
    HashTable(int s);
    void insertLinear(const std::string& key);
    void insertQuadratic(const std::string& key);
    void insertDoubleHashing(const std::string& key);
    int hash1(const std::string& key);
    int hash2(const std::string& key);
    void remove(const std::string& key);
    void draw();
    ~HashTable();
};

#endif // HASH_TABLE_H