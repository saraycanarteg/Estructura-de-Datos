#include "OpenHashing.h"

OpenHashing::OpenHashing(int s) {
    size = s;
    table = new Node*[size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

int OpenHashing::hashFunction(int key) {
    return key % size;
}

void OpenHashing::insert(int key) {
    int index = hashFunction(key);
    Node* newNode = new Node(key);
    newNode->next = table[index];
    table[index] = newNode;
}

void OpenHashing::display() {
    cleardevice();
    for (int i = 0; i < size; i++) {
        int x = 50, y = 50 + (i * 50);
        setcolor(WHITE);
        rectangle(x, y, x + 50, y + 50);
        outtextxy(x + 15, y + 15, (char*)(to_string(i).c_str()));
        Node* temp = table[i];
        int offset = 60;
        while (temp) {
            rectangle(x + offset, y, x + offset + 50, y + 50);
            outtextxy(x + offset + 15, y + 15, (char*)(to_string(temp->key).c_str()));
            offset += 60;
            temp = temp->next;
        }
    }
}

OpenHashing::~OpenHashing() {
    for (int i = 0; i < size; i++) {
        Node* temp = table[i];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
    delete[] table;
}