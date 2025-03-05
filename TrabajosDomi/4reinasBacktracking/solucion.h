// solucion.h
#ifndef SOLUCION_H
#define SOLUCION_H

#include <graphics.h>
#include <vector>
#include <string>

class ChessBoard {
private:
    const int BOARD_SIZE = 4;
    std::vector<std::vector<int>> solutions;
    
    // Tracking variables
    int totalNodesExplored = 0;
    int backtrackingSteps = 0;
    int pruningSteps = 0;

    // Visualization and tracking methods
    void drawStatus(const std::string& message);
    void drawBoard(const std::vector<int>& currentBoard);
    void drawQueens(const std::vector<int>& queenPositions);
    void animateBacktracking(const std::vector<int>& board, int row, 
                             const std::string& status);
    void displaySearchStatistics();
    
    bool isSafe(const std::vector<int>& board, int row, int col);
    void solveNQueensUtil(std::vector<int>& board, int row);

public:
    void solveNQueens(int boardSize);
};

#endif // SOLUCION_H