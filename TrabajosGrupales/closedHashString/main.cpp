#include <graphics.h>
#include <iostream>
#include "hashTable.h"

int main() {
    int tableSize;
    std::cout << "Enter the size of the hash table: ";
    std::cin >> tableSize;
    
    initwindow(1300, 800);
    HashTable table(tableSize);
    
  int option;
    std::string key;
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
            std::cout << "Enter string key: ";
            std::cin.ignore(); // Clear buffer
            std::getline(std::cin, key);
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


