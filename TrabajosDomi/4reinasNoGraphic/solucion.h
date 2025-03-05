// solucion.h
#ifndef SOLUCION_H
#define SOLUCION_H

#include <vector>
#include <string>
#include <iostream>

class ChessBoard {
private:
    const int BOARD_SIZE = 4;
    std::vector<std::vector<int>> solutions;
    
    // Tracking variables
    int totalNodesExplored = 0;
    int backtrackingSteps = 0;
    int pruningSteps = 0;

    // Console visualization methods
    void printBoard(const std::vector<int>& board);
    void displaySearchStatistics();
    
    bool isSafe(const std::vector<int>& board, int row, int col);
    void solveNQueensUtil(std::vector<int>& board, int row);

public:
    void solveNQueens(int boardSize);
};

#endif // SOLUCION_H