#ifndef PDF_GENERATOR_H
#define PDF_GENERATOR_H

#include <string>
#include <vector>

struct GameRecord {
    std::string playerName;
    int score;
    std::string date;
};

void createGameRecordsPDF(const std::vector<GameRecord>& records, const std::string& outputFile);

#endif // PDF_GENERATOR_H