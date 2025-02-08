#include <graphics.h>
#include <iostream>

class HashTable {
private:
    class HashNode {
    public:
        int key;
        bool occupied;
        HashNode(int k) : key(k), occupied(true) {}
    };
    
    int size;
    HashNode** table;
    
    int hash1(int key) {
        return key % size;
    }
    
    int hash2(int key) {
        return (key * 7) % (size - 1) + 1;
    }

public:
    HashTable(int s) : size(s) {
        table = new HashNode*[size];
        for (int i = 0; i < size; i++) table[i] = nullptr;
    }
    
    void insertLinear(int key) {
        int index = hash1(key);
        int i = 0;
        while (table[index] != nullptr && table[index]->occupied) {
            index = (hash1(key) + i) % size;
            i++;
        }
        table[index] = new HashNode(key);
    }
    
    void insertQuadratic(int key) {
        int index = hash1(key);
        int i = 0;
        while (table[index] != nullptr && table[index]->occupied) {
            index = (hash1(key) + i * i) % size;
            i++;
        }
        table[index] = new HashNode(key);
    }
    
    void insertDoubleHashing(int key) {
        int index = hash1(key);
        int step = 7 - (key % 7); // Nuevo cálculo de hash2 según la imagen
        int i = 0;
    
        while (table[index] != nullptr && table[index]->occupied) {
            index = (hash1(key) + i * step) % size; // Aplicando f(i) = i × hash2(key)
            i++;
        }
    
        table[index] = new HashNode(key);
    }    
    
    void remove(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int start = index;
        while (table[index] != nullptr) {
            if (table[index]->key == key) {
                table[index]->occupied = false;
                return;
            }
            index = (index + step) % size;
            if (index == start) break;
        }
    }
    
    void draw() {
        cleardevice();
        int cols = 10;
        int rows = (size + cols - 1) / cols;
        for (int i = 0; i < size; i++) {
            int x = 100 + (i % cols) * 140;
            int y = 100 + (i / cols) * 140;
            rectangle(x, y, x + 130, y + 130);
            char str[10];
            sprintf(str, "%d", i);
            setcolor(BLUE);
            outtextxy(x + 50, y + 140, str);
            if (table[i] != nullptr && table[i]->occupied) {
                sprintf(str, "%d", table[i]->key);
                setcolor(WHITE);
                outtextxy(x + 50, y + 50, str);
            }
        }
    }
    
    ~HashTable() {
        for (int i = 0; i < size; i++) delete table[i];
        delete[] table;
    }
};

int main() {
    int tableSize;
    std::cout << "Enter the size of the hash table: ";
    std::cin >> tableSize;
    
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    initwindow(1600, 1000);
    HashTable table(tableSize);
    
    int option, key;
    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Insert Linear Probing" << std::endl;
        std::cout << "2. Insert Quadratic Probing" << std::endl;
        std::cout << "3. Insert Double Hashing" << std::endl;
        std::cout << "4. Remove Element" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;
        
        if (option >= 1 && option <= 4) {
            std::cout << "Enter key: ";
            std::cin >> key;
        }
        
        switch (option) {
            case 1: table.insertLinear(key); break;
            case 2: table.insertQuadratic(key); break;
            case 3: table.insertDoubleHashing(key); break;
            case 4: table.remove(key); break;
            case 5: break;
            default: std::cout << "Invalid option!" << std::endl;
        }
        
        table.draw();
    } while (option != 5);
    
    closegraph();
    return 0;
}
