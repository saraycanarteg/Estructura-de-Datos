#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record {
private:
    std::string name;
    int score;
    Record* next;

public:
    Record(const std::string& playerName = "", int playerScore = 0);
    
    // Getters
    std::string getName() const;
    int getScore() const;
    Record* getNext() const;
    
    // Setters
    void setNext(Record* nextRecord);
    
    friend class RecordManager;
};
#endif