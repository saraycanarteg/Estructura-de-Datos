// solucion.cpp
#include "solucion.h"
#include <iostream>
#include <iomanip>

void ChessBoard::printBoard(const std::vector<int>& board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row] == col) {
                std::cout << " Q "; // Queen
            } else {
                std::cout << " . "; // Empty square
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ChessBoard::displaySearchStatistics() {
    std::cout << "\n--- Estadísticas de Búsqueda ---" << std::endl;
    std::cout << "Nodos explorados: " << totalNodesExplored << std::endl;
    std::cout << "Pasos de backtracking: " << backtrackingSteps << std::endl;
    std::cout << "Podas realizadas: " << pruningSteps << std::endl;
    std::cout << "Soluciones encontradas: " << solutions.size() << std::endl;
    
    std::cout << "\n--- Soluciones Encontradas ---" << std::endl;
    for (const auto& solution : solutions) {
        printBoard(solution);
    }
}

bool ChessBoard::isSafe(const std::vector<int>& board, int row, int col) {
    totalNodesExplored++;
    
    for (int i = 0; i < row; i++) {
        // Check same column
        if (board[i] == col) {
            pruningSteps++;
            return false;
        }
        
        // Check diagonals
        if (abs(board[i] - col) == abs(i - row)) {
            pruningSteps++;
            return false;
        }
    }
    return true;
}

void ChessBoard::solveNQueensUtil(std::vector<int>& board, int row) {
    // Base case: all queens are placed
    if (row == BOARD_SIZE) {
        solutions.push_back(board);
        return;
    }

    // Try placing queen in each column of this row
    for (int col = 0; col < BOARD_SIZE; col++) {
        if (isSafe(board, row, col)) {
            // Place the queen
            board[row] = col;

            // Recurse for next row
            solveNQueensUtil(board, row + 1);

            // Backtrack: remove queen for next iteration
            backtrackingSteps++;
            board[row] = -1;
        }
    }
}

void ChessBoard::solveNQueens(int boardSize) {
    // Initialize board with -1 (no queens placed)
    std::vector<int> board(boardSize, -1);

    // Reset tracking variables
    totalNodesExplored = 0;
    backtrackingSteps = 0;
    pruningSteps = 0;
    solutions.clear();

    // Start solving from first row
    solveNQueensUtil(board, 0);

    // Display search statistics and solutions
    displaySearchStatistics();
}