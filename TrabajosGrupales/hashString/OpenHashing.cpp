#include "OpenHashing.h"
#include <graphics.h>
#include <iostream>
#include <bitset>
#include <cmath>
#include <iomanip>
using namespace std;

double zoomLevel = 1.0; // Initialize zoomLevel

OpenHashing::OpenHashing(int s) {
    size = s;
    table = new Node*[size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

int OpenHashing::hashFunction(const string& key) {
    cout << "\n========= Hash Calculation for '" << key << "' =========\n" << std::endl;
    
    bitset<32> hashValue(0);
    cout << "Initial value: " << hashValue << endl;
    
    // Process characters in reverse order
    for (int i = key.length() - 1; i >= 0; i--) {
        char c = key[i];
        cout << "\n----- Processing character '" << c << "' (ASCII: " << (int)c << ") -----" << endl;
        
        // Step 1: Add ASCII value
        unsigned long currentValue = hashValue.to_ulong();
        currentValue += static_cast<unsigned int>(c);
        hashValue = bitset<32>(currentValue);
        
        cout << "1. After adding ASCII value:" << endl;
        cout << "   " << hashValue << endl;

        // If this is not the first character (i > 0), continue with hash process
        if (i > 0) {
            // Step 2: Extract first 4 bits (most significant bits)
            unsigned long firstFourBits = 0;
            for (int j = 31; j >= 28; j--) {
                firstFourBits = (firstFourBits << 1) | hashValue[j];
            }
            cout << "2. First 4 bits extracted: " << bitset<4>(firstFourBits) << endl;
            
            // Step 3: Shift main value
            hashValue <<= 4;
            cout << "3. After shifting 4 positions:" << endl;
            cout << "   " << hashValue << endl;
            
            // Step 4: Create and apply mask for XOR
            bitset<32> mask(0);
            mask = bitset<32>(firstFourBits << 19);
            cout << "4. Mask for XOR (bits 19-22):" << endl;
            cout << "   " << mask << std::endl;
            
            // Step 5: XOR operation
            hashValue ^= mask;
            cout << "5. Final result after XOR:" << endl;
            cout << "   " << hashValue << endl;
        }
    }
    
    // Calculate final hash value
    unsigned long finalValue = hashValue.to_ulong();
    int hashIndex = finalValue % size;
    
    cout << "\n========= Final Results ==========" << endl;
    cout << "Binary value: " << hashValue << endl;
    cout << "Decimal value: " << finalValue << endl;
    cout << "Hash index (mod " << size << "): " << hashIndex <<endl;
    cout << "=================================" << endl;
    
    return hashIndex;
}

void OpenHashing::display() {
    cleardevice();
    
    int boxWidth = 60;
    int boxHeight = 40;
    int startX = 50;
    int startY = getmaxy() - 150; // Mantiene la tabla hash en la parte inferior
    int horizontalSpacing = 90;
    
    // Dibujar cajas de índice en una sola fila
    for (int i = 0; i < size; i++) {
        int x = startX + (i * horizontalSpacing);
        
        setcolor(WHITE);
        rectangle(x, startY, x + boxWidth, startY + boxHeight);
        std::string indexStr = std::to_string(i);

        outtextxy(x + boxWidth / 3, startY + boxHeight / 3, (char*)(indexStr.c_str()));
        
        // Dibujar elementos encadenados encima del índice
        Node* temp = table[i];
        int verticalOffset = -50;  // Volvemos a usar offset negativo para ir hacia arriba
        
        while (temp) {
            rectangle(x, startY + verticalOffset, x + boxWidth, startY + verticalOffset + boxHeight);
            int textX = x + (boxWidth - textwidth((char*)temp->key.c_str())) / 2;
            int textY = startY + verticalOffset + (boxHeight - textheight((char*)temp->key.c_str())) / 2;
            outtextxy(textX, textY, (char*)(temp->key.c_str()));
            verticalOffset -= 50;  // Decrementar para subir al siguiente elemento
            temp = temp->next;
        }
    }
}


void OpenHashing::insert(const string& key) {
    int index = hashFunction(key);
    Node* newNode = new Node(key);

    // Insertar al final de la lista en esa posición
    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        Node* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
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

