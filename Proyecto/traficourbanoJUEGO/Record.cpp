#include "Record.h"

Record::Record(const std::string& playerName, int playerScore) 
    : name(playerName), score(playerScore), next(nullptr) {}

std::string Record::getName() const {
    return name;
}

int Record::getScore() const {
    return score;
}

Record* Record::getNext() const {
    return next;
}

void Record::setNext(Record* nextRecord) {
    next = nextRecord;
}