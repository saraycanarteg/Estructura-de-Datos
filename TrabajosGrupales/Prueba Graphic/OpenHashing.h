#include <graphics.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Node {
public:
    int key;
    Node* next;
    Node(int k) : key(k), next(nullptr) {}
};

class OpenHashing {
private:
    Node** table;
    int size;

public:
    OpenHashing(int s);
   
    int hashFunction(int key);

    void insert(int key);

    void display();

    ~OpenHashing();

    void remove(int key);
};