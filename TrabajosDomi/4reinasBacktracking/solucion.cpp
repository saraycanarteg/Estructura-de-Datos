// solucion.cpp
#include "solucion.h"
#include <iostream>
#include <graphics.h>
#include <unistd.h>  // for usleep

void ChessBoard::drawStatus(const std::string& message) {
    // Clear status area
    setfillstyle(SOLID_FILL, WHITE);
    bar(50, 500, 450, 550);
    
    // Draw status text
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(60, 510, const_cast<char*>(message.c_str()));
}

void ChessBoard::drawBoard(const std::vector<int>& currentBoard) {
    cleardevice();

    // Set up board colors
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);

    // Draw chess board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int x1 = 100 + j * 100;
            int y1 = 100 + i * 100;
            int x2 = x1 + 100;
            int y2 = y1 + 100;

            // Alternate board colors
            if ((i + j) % 2 == 0) {
                setfillstyle(SOLID_FILL, WHITE);
            } else {
                setfillstyle(SOLID_FILL, LIGHTGRAY);
            }

            bar(x1, y1, x2, y2);
            rectangle(x1, y1, x2, y2);
        }
    }
}

void ChessBoard::drawQueens(const std::vector<int>& queenPositions) {
    // Draw queens on the board
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);

    for (int row = 0; row < BOARD_SIZE; row++) {
        if (queenPositions[row] != -1) {
            int col = queenPositions[row];
            int x = 150 + col * 100;
            int y = 150 + row * 100;
            
            // Draw a circle to represent the queen
            circle(x, y, 30);
            floodfill(x, y, RED);
        }
    }
}

void ChessBoard::animateBacktracking(const std::vector<int>& board, 
                                     int row, 
                                     const std::string& status) {
    // Prepare board visualization
    drawBoard(board);
    drawQueens(board);
    drawStatus(status);

    // Much shorter delay
    usleep(50000);  // 0.05 seconds
}

void ChessBoard::displaySearchStatistics() {
    // Clear screen for statistics
    cleardevice();
    
    // Set text style
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    
    // Prepare statistics strings
    char totalNodes[100];
    char backtrackSteps[100];
    char pruningCount[100];
    char solutionsFound[100];
    
    sprintf(totalNodes, "Nodos explorados: %d", totalNodesExplored);
    sprintf(backtrackSteps, "Pasos de backtracking: %d", backtrackingSteps);
    sprintf(pruningCount, "Podas realizadas: %d", pruningSteps);
    sprintf(solutionsFound, "Soluciones encontradas: %d", solutions.size());
    
    // Display statistics
    outtextxy(50, 100, (char*)"Estadisticas de Busqueda:");
    outtextxy(50, 150, totalNodes);
    outtextxy(50, 200, backtrackSteps);
    outtextxy(50, 250, pruningCount);
    outtextxy(50, 300, solutionsFound);
    
    // Wait for key press
    getch();
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
    // Visualize current state before processing
    animateBacktracking(board, row, "Explorando fila " + std::to_string(row));

    // Base case: all queens are placed
    if (row == BOARD_SIZE) {
        solutions.push_back(board);
        
        // Visualize solution found
        animateBacktracking(board, row, "¡Solución encontrada!");
        
        return;
    }

    // Try placing queen in each column of this row
    for (int col = 0; col < BOARD_SIZE; col++) {
        // Visualize current column being checked
        animateBacktracking(board, row, 
            "Probando reina en fila " + std::to_string(row) + 
            ", columna " + std::to_string(col));

        if (isSafe(board, row, col)) {
            // Place the queen
            board[row] = col;

            // Visualize queen placement
            animateBacktracking(board, row, 
                "Reina colocada en fila " + std::to_string(row) + 
                ", columna " + std::to_string(col));

            // Recurse for next row
            solveNQueensUtil(board, row + 1);

            // Backtrack: remove queen for next iteration
            backtrackingSteps++;
            animateBacktracking(board, row, 
                "Retrocediendo de fila " + std::to_string(row));
            board[row] = -1;
        }
    }
}

void ChessBoard::solveNQueens(int boardSize) {
    // Initialize graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Initialize board with -1 (no queens placed)
    std::vector<int> board(boardSize, -1);

    // Reset tracking variables
    totalNodesExplored = 0;
    backtrackingSteps = 0;
    pruningSteps = 0;
    solutions.clear();

    // Start solving from first row
    solveNQueensUtil(board, 0);

    // Display search statistics
    displaySearchStatistics();

    // Close graphics
    closegraph();
}