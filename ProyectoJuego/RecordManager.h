#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include "Record.h"
#include <string>

class RecordManager {
private:
    Record* head;
    const int MAX_RECORDS = 10;

    void sortRecords();
    void trimRecords();

public:
    RecordManager();
    ~RecordManager();
    
    void addRecord(const std::string& name, int score);
    void loadRecords();
    void saveRecords();
    void displayRecords(int x, int y);
    
    // Helper to get the head of the list (for iteration if needed)
    Record* getHead() const;
};
#endif