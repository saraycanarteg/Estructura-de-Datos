#include "HashTable.h"

HashTable::HashNode::HashNode(const std::string& k) : key(k), occupied(true) {}

HashTable::HashTable(int s) : size(s) {
    table = new HashNode*[size];
    for (int i = 0; i < size; i++) table[i] = nullptr;
}

int HashTable::hashFunction(const std::string& key) {
    std::bitset<32> hashValue(0);
    
    for (int i = key.length() - 1; i >= 0; i--) {
        char c = key[i];
        unsigned long currentValue = hashValue.to_ulong();
        currentValue += static_cast<unsigned int>(c);
        hashValue = std::bitset<32>(currentValue);

        if (i > 0) {
            unsigned long firstFourBits = 0;
            for (int j = 31; j >= 28; j--) {
                firstFourBits = (firstFourBits << 1) | hashValue[j];
            }
            
            hashValue <<= 4;
            
            std::bitset<32> mask(0);
            mask = std::bitset<32>(firstFourBits << 19);
            hashValue ^= mask;
        }
    }
    
    unsigned long finalValue = hashValue.to_ulong();
    return finalValue;
}

int HashTable::hash1 (const std::string& key)  {
    int stringValue = hashFunction(key);
    return stringValue %size;
}
int HashTable::hash2 (const std::string& key)  {
    int stringValue = hashFunction(key);
    return 7- (stringValue %7);
}

void HashTable::insertLinear(const std::string& key) {
    int index = hash1(key);
    int i = 0;
    while (table[index] != nullptr && table[index]->occupied) {
        index = (hash1(key) + i) % size;
        i++;
    }
    table[index] = new HashNode(key);
}

void HashTable::insertQuadratic(const std::string& key) {
    int index = hash1(key);
    int i = 0;
    while (table[index] != nullptr && table[index]->occupied) {
        index = (hash1(key)+ i * i) % size;
        i++;
    }
    table[index] = new HashNode(key);
}

void HashTable::insertDoubleHashing(const std::string& key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;
    
    while (table[index] != nullptr && table[index]->occupied) {
        i++;
        index = (hash1(key) + i * step) % size;
        
        if (i >= size) {
            std::cout << "Error: La tabla está llena o no se puede encontrar una posición válida" << std::endl;
            return;
        }
    }
    
    table[index] = new HashNode(key);
}

void HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    int start = index;
    int step = 1;
    while (table[index] != nullptr) {
        if (table[index]->key == key) {
            table[index]->occupied = false;
            return;
        }
        index = (index + step) % size;
        if (index == start) break;
    }
}

void HashTable::draw() {
    cleardevice();
    
    int windowWidth = getmaxx();
    int windowHeight = getmaxy();
    
    int cellWidth = 100;
    int cellHeight = 100;
    int cols = 10;
    int rows = (size + cols - 1) / cols;
    
    int spacingX = 20;
    int spacingY = 20;
    
    int tableWidth = cols * (cellWidth + spacingX) - spacingX;
    int tableHeight = rows * (cellHeight + spacingY) - spacingY;
    
    int startX = (windowWidth - tableWidth) / 2;
    int startY = (windowHeight - tableHeight) / 2;

    for (int i = 0; i < size; i++) {
        int x = startX + (i % cols) * (cellWidth + spacingX);
        int y = startY + (i / cols) * (cellHeight + spacingY);

        rectangle(x, y, x + cellWidth, y + cellHeight);
        
        char str[10];
        sprintf(str, "%d", i);
        setcolor(YELLOW);
        outtextxy(x + cellWidth / 3, y + cellHeight + 5, str);
        
        if (table[i] != nullptr && table[i]->occupied) {
            setcolor(YELLOW);
            outtextxy(x + 10, y + cellHeight / 3, (char*)table[i]->key.c_str());
        }
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < size; i++) delete table[i];
    delete[] table;
}