#include "NReinas.h"

NReinas::NReinas(int size) {
    n = size;
    tablero = new int[n * n]{};
}

NReinas::~NReinas() {
    delete[] tablero;
}

bool NReinas::esSeguro(int fila, int col) {
    for (int i = 0; i < col; i++) {
        if (*(tablero + fila * n + i)) return false;
    }
    for (int i = fila, j = col; i >= 0 && j >= 0; i--, j--) {
        if (*(tablero + i * n + j)) return false;
    }
    for (int i = fila, j = col; i < n && j >= 0; i++, j--) {
        if (*(tablero + i * n + j)) return false;
    }
    return true;
}

bool NReinas::resolverNReinas(int col) {
    if (col >= n) return true;
    for (int i = 0; i < n; i++) {
        if (esSeguro(i, col)) {
            *(tablero + i * n + col) = 1;
            if (resolverNReinas(col + 1)) return true;
            *(tablero + i * n + col) = 0;
        }
    }
    return false;
}

void NReinas::mostrarTablero() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int cellSize = 50;
    int offset = 50;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x1 = offset + j * cellSize;
            int y1 = offset + i * cellSize;
            int x2 = x1 + cellSize;
            int y2 = y1 + cellSize;
            setfillstyle(SOLID_FILL, (i + j) % 2 == 0 ? WHITE : LIGHTGRAY);
            bar(x1, y1, x2, y2);
            rectangle(x1, y1, x2, y2);
            if (*(tablero + i * n + j) == 1) {
                setfillstyle(SOLID_FILL, RED);
                fillellipse((x1 + x2) / 2, (y1 + y2) / 2, cellSize / 3, cellSize / 3);
            }
        }
    }
    getch();
    closegraph();
}

void NReinas::resolver() {
    if (resolverNReinas(0)) {
        mostrarTablero();
    } else {
        std::cout << "No hay solución para " << n << " reinas." << std::endl;
    }
}