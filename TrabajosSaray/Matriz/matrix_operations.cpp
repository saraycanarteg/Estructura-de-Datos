#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"
#include <random>

template<typename T>
class MatrixOperations {
public:
    static Matrix<T> generateRandomMatrix(size_t rows, size_t cols, T min, T max) {
        Matrix<T> matrix(rows, cols);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix.at(i, j) = static_cast<T>(dis(gen));
            }
        }
        return matrix;
    }
};

#endif