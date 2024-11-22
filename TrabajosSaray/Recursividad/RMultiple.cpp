#include <stdio.h>

int sumSquares(int n, int m) {
    if (n == 0 || m == 0) {
        return 0;
    } else {
        return n * n + m * m + sumSquares(n - 1, m - 1);
    }
}

int main() {
    int n = 4, m = 2;
    int result = sumSquares(n, m);
    printf("La suma de los cuadrados de %d y %d es: %d\n", n, m, result);
    return 0;
}