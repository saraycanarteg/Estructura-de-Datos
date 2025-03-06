#include "RecordManager.h"
#include <fstream>
#include <graphics.h>
#include <cstring>

RecordManager::RecordManager() : head(nullptr) {}

RecordManager::~RecordManager() {
    while (head != nullptr) {
        Record* temp = head;
        head = head->next;
        delete temp;
    }
}

void RecordManager::addRecord(const std::string& name, int score) {
    Record* newRecord = new Record(name, score);
    
    // If list is empty
    if (head == nullptr) {
        head = newRecord;
        return;
    }
    
    // If new record should be at the start
    if (score > head->score) {
        newRecord->next = head;
        head = newRecord;
    }
    else {
        Record* current = head;
        while (current->next != nullptr && current->next->score >= score) {
            current = current->next;
        }
        newRecord->next = current->next;
        current->next = newRecord;
    }
    
    // Trim to max records
    trimRecords();
}

void RecordManager::trimRecords() {
    int count = 0;
    Record* current = head;
    
    while (current != nullptr && count < MAX_RECORDS) {
        current = current->next;
        count++;
    }
    
    // If more than max records, delete extras
    if (current != nullptr) {
        Record* prev = head;
        for (int i = 0; i < count - 1; i++) {
            prev = prev->next;
        }
        
        // Delete extra records
        while (current != nullptr) {
            Record* temp = current;
            current = current->next;
            delete temp;
        }
        prev->next = nullptr;
    }
}

void RecordManager::loadRecords() {
    // Clear existing records
    while (head != nullptr) {
        Record* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    
    // Try to load from file
    std::ifstream inFile("records.txt");
    if (!inFile) return;
    
    std::string name;
    int score;
    
    while (inFile >> name >> score) {
        addRecord(name, score);
    }
    
    inFile.close();
}

void RecordManager::saveRecords() {
    std::ofstream outFile("records.txt");
    
    Record* current = head;
    while (current != nullptr) {
        outFile << current->getName() << " " << current->getScore() << std::endl;
        current = current->next;
    }
    
    outFile.close();
}

void RecordManager::displayRecords(int x, int y) {
    cleardevice();
    setbkcolor(GREEN);
    cleardevice();
    setcolor(WHITE);
    
    // Title
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(x, y - 50, (char*)"TOP 10 RECORDS");
    
    // Display records
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    
    Record* current = head;
    int i = 0;
    while (current != nullptr && i < MAX_RECORDS) {
        char recordText[100];
        sprintf(recordText, "%d. %s - %d puntos", 
                i+1, current->getName().c_str(), current->getScore());
        outtextxy(x, y + i*30, recordText);
        
        current = current->next;
        i++;
    }
    
    // Wait for key press
    getch();
}

Record* RecordManager::getHead() const {
    return head;
}