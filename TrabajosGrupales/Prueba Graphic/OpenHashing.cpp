#include "OpenHashing.h"

OpenHashing::OpenHashing(int s)
{
    size = s;
    table = new Node *[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = nullptr;
    }
}

int OpenHashing::hashFunction(int key)
{
    return key % size;
}

void OpenHashing::insert(int key)
{
    int index = hashFunction(key);
    Node *newNode = new Node(key);
    newNode->next = table[index];
    table[index] = newNode;
}

void OpenHashing::display() {
    cleardevice();
    int startX = 30;        
    int startY = 30;        
    int boxWidth = 40;      
    int boxHeight = 40;     
    int horizontalGap = 60; 
    int verticalGap = 100;  

    // Draw table headers and boxes
    for (int i = 0; i < size; i++) {
        int x = startX + (i * (boxWidth + horizontalGap));
        setcolor(WHITE);

        // Draw index box
        rectangle(x, startY, x + boxWidth, startY + boxHeight);
        outtextxy(x + 15, startY + 15, (char*)(to_string(i).c_str()));

        // Draw hash calculation with process
        if (table[i]) {
            char hashInfo[100];
            sprintf(hashInfo, "H(%d)=%d mod %d = %d", 
                    table[i]->key, table[i]->key, size, hashFunction(table[i]->key));
            outtextxy(x - 10, startY - 20, hashInfo);
        }

        // Draw linked elements
        Node* temp = table[i];
        int offset = 0;
        while (temp) {
            setcolor(LIGHTGREEN);
            rectangle(x, startY + boxHeight + 10 + offset,
                     x + boxWidth, startY + 2*boxHeight + 10 + offset);
            outtextxy(x + 15, startY + boxHeight + 25 + offset,
                     (char*)(to_string(temp->key).c_str()));

            if (temp->next) {
                line(x + boxWidth/2, startY + 2*boxHeight + 10 + offset,
                     x + boxWidth/2, startY + 2*boxHeight + 25 + offset);
                line(x + boxWidth/2 - 5, startY + 2*boxHeight + 20 + offset,
                     x + boxWidth/2, startY + 2*boxHeight + 25 + offset);
                line(x + boxWidth/2 + 5, startY + 2*boxHeight + 20 + offset,
                     x + boxWidth/2, startY + 2*boxHeight + 25 + offset);
            }

            offset += boxHeight + 15;
            temp = temp->next;
        }
    }

    // Draw detailed hash calculation steps
    setcolor(WHITE);
    int textY = getmaxy() - 300;
    outtextxy(50, textY, "Hash Calculation Process:");
    textY += 20;
    for (int i = 0; i < size; i++) {
        if (table[i]) {
            char stepInfo[200];
            sprintf(stepInfo, "Value %d -> Binary: %032b -> Mod %d = Index %d", 
                    table[i]->key, table[i]->key, size, hashFunction(table[i]->key));
            outtextxy(50, textY, stepInfo);
            textY += 20;
        }
    }
}

OpenHashing::~OpenHashing()
{
    for (int i = 0; i < size; i++)
    {
        Node *temp = table[i];
        while (temp)
        {
            Node *toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
    delete[] table;
}

void OpenHashing::remove(int key) {
    int index = hashFunction(key);
    Node* current = table[index];
    Node* prev = nullptr;

    // Search for key
    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    // Key found
    if (current != nullptr) {
        // Case 1: Element is at head
        if (prev == nullptr) {
            table[index] = current->next;
        }
        // Case 2: Element is in middle or end
        else {
            prev->next = current->next;
        }
        delete current;
    }
    // Key not found - no action needed
}